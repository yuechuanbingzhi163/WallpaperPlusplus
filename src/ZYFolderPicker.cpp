#include "ZYFolderPicker.h"
#include "ZYScanner.h"

namespace DuiLib {

ZYFolderPicker::ZYFolderPicker(ZYFolderPickerListener *cb) : m_cb(cb), m_list(NULL) {
}

LRESULT ZYFolderPicker::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (WM_CREATE == uMsg) {
		m_paintManagerUi.Init(m_hWnd);
		m_paintManagerUi.AttachDialog(CDialogBuilder().Create(_T("folderpicker.xml"), NULL, NULL, &m_paintManagerUi));
		m_paintManagerUi.AddNotifier(this);
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
	}
	LRESULT res;
	if (m_paintManagerUi.MessageHandler(uMsg, wParam, lParam, res)) {
		return res;
	}
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

void ZYFolderPicker::Notify(TNotifyUI& msg) {
	if (!_tcscmp(msg.sType, _T("windowinit"))) {
		OnCreate();
	}
	else if (!_tcscmp(msg.sType, _T("click"))) {
		if (!_tcscmp(msg.pSender->GetName(), _T("closebutton")) || !_tcscmp(msg.pSender->GetName(), _T("cancelbutton"))) {
			Close();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("okbutton"))) {
			if (m_cb) {
				m_cb->OnDir(m_dir.GetData());
			}
			Close();
		}
	} else if (!_tcscmp(msg.sType, _T("itemselect"))) {
		OnItemSelect();
	}
}

LPCTSTR ZYFolderPicker::GetWindowClassName() const {
	return _T("ZYFolderPicker");
}

VOID ZYFolderPicker::LoadItems(LPCTSTR dir) {
	m_list->RemoveAll();
	if (dir[0] != _T('\0')) {
		vector<CStdString> foldernames;
		foldernames = ZYScanner().Scan(dir, FILE_ATTRIBUTE_DIRECTORY);
		AddItem(_T("."));
		AddItem(_T(".."));
		for (vector<CStdString>::iterator it = foldernames.begin(); it != foldernames.end(); it++) {
			CStdString &foldername = *it;
			if (_tcscmp(foldername.GetData(), _T(".")) && _tcscmp(foldername.GetData(), _T(".."))) {
				AddItem(foldername.GetData());
			}
		}
	} else {
		TCHAR drives[PATH_MAX];
		::GetLogicalDriveStrings(PATH_MAX, drives);
		for (TCHAR *drive = drives; *drive && drive < &drives[PATH_MAX]; drive += _tcslen(drive) + 1) {
			AddItem(drive);
		}
	}
}

VOID ZYFolderPicker::AddItem(LPCTSTR foldername) {
	CControlUI* control;
	if ((control = CDialogBuilder().Create(_T("folderpickeritem.xml"), NULL, NULL, &m_paintManagerUi))) {
		CLabelUI *label;
		m_list->Add(control);
		if ((label = (CLabelUI *) m_paintManagerUi.FindSubControlByClass(control, _T("LabelUI")))) {
			label->SetText(foldername);
		}
	}
}

VOID ZYFolderPicker::OnCreate() {
	if ((m_list = (CListUI *) m_paintManagerUi.FindControl(_T("list")))) {
		m_dir = CPaintManagerUI::GetCurrentPath();
		LoadItems(m_dir.GetData());
	}
}

VOID ZYFolderPicker::OnItemSelect() {
	CLabelUI *label;
	if ((label = (CLabelUI *) m_paintManagerUi.FindSubControlByClass(m_list->GetItemAt(m_list->GetCurSel()), _T("LabelUI")))) {
		CStdString foldername = label->GetText();
		if (foldername.Compare(_T("."))) {
			if (foldername.Compare(_T(".."))) {
				if (foldername.GetAt(foldername.GetLength() - 1) != _T('\\')) {
					m_dir.Format(_T("%s\\%s"), m_dir.GetData(), foldername.GetData());
				} else {
					m_dir = foldername;
				}
			} else {
				m_dir = m_dir.Left(m_dir.Left(m_dir.GetLength() - 1).ReverseFind(_T('\\')));
			}
		}
		LoadItems(m_dir.GetData());
	}
}

}
