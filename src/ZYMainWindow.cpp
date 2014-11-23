///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYMainWindow.cpp
/// @brief 主窗口
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYMainWindow.h"
#include "ZYConfigurator.h"
#include "ZYDbHelper.h"
#include "ZYContainerUi.h"
#include "ZYSetter.h"
#include "ZYScanner.h"
#include "ZYWallpaperHelper.h"
#include "Resource.h"

namespace DuiLib {

#define ZYPROGRESS (WM_USER + 1)
#define ZYFILE (WM_USER + 2)
#define ZYSHOW (WM_USER + 3)

ZYMainWindow::ZYMainWindow() : m_list(NULL), m_combobox(NULL) {
	m_imageSniffer = new ZYImageSniffer(this);
}

ZYMainWindow::~ZYMainWindow() {
	if (m_imageSniffer) delete m_imageSniffer;
}

CControlUI* ZYMainWindow::CreateControl(LPCTSTR pstrClass) {
	if (!_tcscmp(pstrClass, _T("ZYListUi"))) {
		return new ZYListUi;
	} else if (!_tcscmp(pstrClass, _T("ZYContainerUi"))) {
		return new ZYContainerUi;
	}
	return NULL;
}

LRESULT ZYMainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_MESSAGE;
	nid.uCallbackMessage = ZYSHOW;
	nid.hIcon = ::LoadIcon(CPaintManagerUI::GetInstance(), (LPCTSTR) IDI_ICON1);
	if (WM_CREATE == uMsg) {
		m_paintManagerUi.Init(m_hWnd);
		m_paintManagerUi.AttachDialog(CDialogBuilder().Create(_T("main.xml"), NULL, this, &m_paintManagerUi));
		m_paintManagerUi.AddNotifier(this);
		::Shell_NotifyIcon(NIM_ADD, &nid);
		return S_OK;
	} else if (WM_DESTROY == uMsg) {
		::Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		return S_OK;
	} else if (uMsg == RegisterWindowMessage(TEXT("TaskbarCreated"))) {
		::Shell_NotifyIcon(NIM_ADD, &nid);
		return S_OK;
	} else if (WM_NCHITTEST == uMsg) {
		POINT point = {
			GET_X_LPARAM(lParam),
			GET_Y_LPARAM(lParam)
		};
		::ScreenToClient(*this, &point);
		RECT rc = m_paintManagerUi.GetCaptionRect();
		if (point.y < rc.bottom) {
			CControlUI* control;
			if ((control = m_paintManagerUi.FindControl(point)) && _tcscmp(control->GetClass(), _T("ButtonUI"))) {
				return HTCAPTION;
			}
		}
		return HTCLIENT;
	} else if (ZYPROGRESS == uMsg) {
		CProgressUI *progress;
		if ((progress = (CProgressUI *) m_paintManagerUi.FindControl(_T("progressbar")))) {
			progress->SetValue(100 <= wParam ? 0 : wParam);
		}
		if (100 == wParam) {
			OnDir(ZYConfigurator::GetInstance()->GetValue(_T("downloaddir")).GetData());
		}
		return S_OK;
	} else if (ZYFILE == uMsg) {
		LPCTSTR filepath = (LPCTSTR) wParam;
		if (ZYImageSniffer::CheckFileextension(filepath) && ZYImageSniffer::CheckImageSize(filepath)) {
			CStdString sql;
			CStdString groupid =  m_combobox->GetItemAt(m_combobox->GetCurSel())->GetUserData();
			sql.Format(_T("INSERT INTO `wallpaper` VALUES('%s', %s); "), filepath, groupid.GetData());
			if (ZYDbHelper::GetInstance()->Query(sql.GetData(), NULL)) {
				AddItem(filepath);
			}
		}
		return S_OK;
	} else if (ZYSHOW == uMsg) {
		if (WM_LBUTTONDBLCLK == lParam) {
			ShowWindow();
		}
		return S_OK;
	}
	LRESULT res;
	if (m_paintManagerUi.MessageHandler(uMsg, wParam, lParam, res)) {
		return res;
	}
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

void ZYMainWindow::Notify(TNotifyUI& msg) {
	if (!_tcscmp(msg.sType, _T("windowinit"))) {
		OnCreate();
	} else if (!_tcscmp(msg.sType, _T("click"))) {
		if (!_tcscmp(msg.pSender->GetName(), _T("closebutton"))) {
			Close();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("selectallbutton"))) {
			SetSelectForAllItems(TRUE);
		} else if (!_tcscmp(msg.pSender->GetName(), _T("cancelallbutton"))) {
			SetSelectForAllItems(FALSE);
		} else if (!_tcscmp(msg.pSender->GetName(), _T("removeselectedbutton"))) {
			ZYDbHelper *dbHelper = ZYDbHelper::GetInstance();
			CStdString groupid = ((CListLabelElementUI *) m_combobox->GetItemAt(m_combobox->GetCurSel()))->GetUserData();
			for (int i = 0; i < m_list->GetCount();) {
				CListContainerElementUI *container = (CListContainerElementUI *) m_list->GetItemAt(i);
				COptionUI *option;
				if ((option = (COptionUI *) m_paintManagerUi.FindSubControlByClass(container, _T("OptionUI"))) && option->IsSelected()) {
					ZYContainerUi *c;
					if (c = (ZYContainerUi *) m_paintManagerUi.FindSubControlByClass(container, _T("ContainerUI"))) {
						CStdString sql;
						sql.Format(_T("DELETE FROM `wallpaper` WHERE path='%s' AND groupid=%s; "), c->GetBkImage(), groupid.GetData());
						if (dbHelper->Query(sql, NULL)) {
							m_list->RemoveAt(i);
						}
					}
				} else {
					i++;
				}
			}
		} else if (!_tcscmp(msg.pSender->GetName(), _T("configurebutton"))) {
			OnConfigureButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("addgroupbutton"))) {
			OnAddGroupButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("deletegroupbutton"))) {
			OnDeleteGroupButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("applybutton"))) {
			OnApplyButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("importbutton"))) {
			OnImportButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("downloadbutton"))) {
			OnDownloadButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("minimizebutton"))) {
			ShowWindow(false);
		}
	} else if (!_tcscmp(msg.sType, _T("itemselect"))) {
		if (!_tcscmp(msg.pSender->GetName(), _T("groupcombobox"))) {
			CStdString groupid = ((CListLabelElementUI *) m_combobox->GetItemAt(m_combobox->GetCurSel()))->GetUserData();
			LoadItemsByGroupid(groupid.GetData());
		}
	} else if (!_tcscmp(msg.sType, _T("itemclick"))) {
		ZYContainerUi *container;
		if ((container = (ZYContainerUi *) m_paintManagerUi.FindSubControlByClass(msg.pSender, _T("ContainerUI")))) {
			ZYWallpaperHelper::GetInstance()->SetWallpaper(container->GetBkImage());
		}
	}
}

LPCTSTR ZYMainWindow::GetWindowClassName() const {
	return _T("ZYMainWindow");
}

VOID ZYMainWindow::OnDir(LPCTSTR dir) {
	vector<CStdString> names = ZYScanner().Scan(dir, ~FILE_ATTRIBUTE_DIRECTORY);
	ZYDbHelper *dbHelper = ZYDbHelper::GetInstance();
	for (vector<CStdString>::iterator it = names.begin(); it != names.end(); it++) {
		CStdString filename = *it;
		CStdString filepath;
		filepath.Format(_T("%s\\%s"), dir, filename.GetData());
		if (ZYImageSniffer::CheckFileextension(filename.GetData()) && ZYImageSniffer::CheckImageSize(filepath)) {
			CStdString sql;
			CStdString groupid =  m_combobox->GetItemAt(m_combobox->GetCurSel())->GetUserData();
			sql.Format(_T("INSERT INTO `wallpaper` VALUES('%s', %s); "), filepath.GetData(), groupid.GetData());
			if (dbHelper->Query(sql.GetData(), NULL)) {
				AddItem(filepath.GetData());
			}
		}
	}
}

VOID ZYMainWindow::OnGroup(LPCTSTR groupname) {
	LoadGroupsAndSelect(groupname);
}

VOID ZYMainWindow::OnProgress(LONG progress) {
	SendMessage(ZYPROGRESS, progress);
}

VOID ZYMainWindow::OnCreate() {
	m_list = (ZYListUi *) m_paintManagerUi.FindControl(_T("list"));
	m_combobox = (CComboUI *)  m_paintManagerUi.FindControl(_T("groupcombobox"));
	LoadGroupsAndSelect(_T(""));
	if (!_tcscmp(ZYConfigurator::GetInstance()->GetValue(_T("autodownload")).GetData(), _T("true"))) {
		OnDownloadButtonClick();
	}
}

VOID ZYMainWindow::OnAddGroupButtonClick() {
	ZYGroupCreator groupcreator(this);
	groupcreator.Create(m_hWnd, _T("ZYGroupCreator"), UI_CLASSSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	groupcreator.CenterWindow();
	::SetWindowLong(groupcreator, GWL_STYLE, (::GetWindowLong(groupcreator, GWL_STYLE) & ~WS_CAPTION) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	groupcreator.ShowModal();
}

VOID ZYMainWindow::OnDeleteGroupButtonClick() {
	ZYDbHelper *dbHelper = ZYDbHelper::GetInstance();
	CListLabelElementUI *item = (CListLabelElementUI *) m_combobox->GetItemAt(m_combobox->GetCurSel());
	CStdString groupid = item->GetUserData();
	CStdString sql;
	sql.Format(_T("DELETE FROM `wallpaper` WHERE groupid=%s; "), groupid.GetData());
	if (dbHelper->Query(sql, NULL)) {
		if (_tcscmp(item->GetText().GetData(), _T("默认"))) {
			sql.Format(_T("DELETE FROM `group` WHERE id=%s; "), groupid.GetData());
			dbHelper->Query(sql, NULL);
		}
	}
	LoadGroupsAndSelect(_T(""));
}

VOID ZYMainWindow::OnApplyButtonClick() {
	CStdString groupid = m_combobox->GetItemAt(m_combobox->GetCurSel())->GetUserData();
	ZYConfigurator::GetInstance()->SetValue(_T("groupid"), groupid.GetData());
}

VOID ZYMainWindow::OnImportButtonClick() {
	ZYFolderPicker folderpicker(this);
	folderpicker.Create(m_hWnd, _T("ZYFolderPicker"), UI_CLASSSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	folderpicker.CenterWindow();
	::SetWindowLong(folderpicker, GWL_STYLE, (::GetWindowLong(folderpicker, GWL_STYLE) & ~WS_CAPTION) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	folderpicker.ShowModal();
}

VOID ZYMainWindow::OnConfigureButtonClick() {
	ZYSetter setter;
	setter.Create(m_hWnd, _T("ZYSetter"), UI_CLASSSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	setter.CenterWindow();
	::SetWindowLong(setter, GWL_STYLE, (::GetWindowLong(setter, GWL_STYLE) & ~WS_CAPTION) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	setter.ShowModal();
}

VOID ZYMainWindow::OnDownloadButtonClick() {
	CStdString url = ZYConfigurator::GetInstance()->GetValue(_T("url"));
	if (!url.IsEmpty()) {
		m_imageSniffer->Sniff(url.GetData());
	}
}

VOID ZYMainWindow::LoadGroupsAndSelect(LPCTSTR groupname) {
	ZYDbHelper *dbHelper = ZYDbHelper::GetInstance();
	vector<vector<CStdString>> qset;
	CComboUI *combobox = (CComboUI *) m_paintManagerUi.FindControl(_T("groupcombobox"));
	if (combobox && dbHelper->Query(_T("SELECT id, name from `group`; "), &qset)) {
		combobox->RemoveAll();
		for (vector<vector<CStdString>>::iterator it = qset.begin(); it != qset.end(); it++) {
			vector<CStdString> &group = *it;
			CListLabelElementUI *item = new CListLabelElementUI;
			item->SetUserData(group[0].GetData());
			item->SetText(group[1].GetData());
			combobox->Add(item);
			if (!_tcscmp(group[1].GetData(), groupname)) {
				item->Select();
			}
		}
		if (-1 == combobox->GetCurSel()) {
			combobox->SelectItem(0);
		}
	}
}

VOID ZYMainWindow::LoadItemsByGroupid(LPCTSTR groupid) {
	m_list->RemoveAll();
	vector<vector<CStdString>> qset;
	CStdString sql;
	sql.Format(_T("SELECT path FROM `wallpaper` WHERE groupid=%s; "), groupid);
	ZYDbHelper::GetInstance()->Query(sql.GetData(), &qset);
	for (vector<vector<CStdString>>::iterator it = qset.begin(); it != qset.end(); it++) {
		vector<CStdString> &paths = *it;
		if (ZYImageSniffer::CheckImageSize(paths[0])) {
			AddItem(paths[0]);
		}
	}
}

VOID ZYMainWindow::AddItem(LPCTSTR filepath) {
	CControlUI* control;
	if ((control = CDialogBuilder().Create(_T("mainitem.xml"), NULL, this, &m_paintManagerUi))) {
		m_list->Add(control);
		CLabelUI *label;
		if ((label = (CLabelUI *) m_paintManagerUi.FindSubControlByClass(control, _T("LabelUI")))) {
			CStdString filename = filepath;
			filename = filename.Mid(filename.ReverseFind(_T('\\')) + 1);
			label->SetText(filename.GetData());
		}
		ZYContainerUi* container;
		if (container = (ZYContainerUi *) m_paintManagerUi.FindSubControlByClass(control, _T("ContainerUI"))) {
			container->SetBkImage(filepath);
		}
	}
}

VOID ZYMainWindow::SetSelectForAllItems(BOOL select) {
	for (int i = 0; i < m_list->GetCount(); i++) {
		COptionUI *option;
		if ((option = (COptionUI *) m_paintManagerUi.FindSubControlByClass(m_list->GetItemAt(i), _T("OptionUI")))) {
			option->Selected(select ? true : false);
		}
	}
}

}