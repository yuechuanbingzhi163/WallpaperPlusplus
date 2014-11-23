///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYSetter.cpp
/// @brief 设置窗口
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月23日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYSetter.h"
#include "ZYConfigurator.h"

namespace DuiLib {

LRESULT ZYSetter::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (WM_CREATE == uMsg) {
		m_paintManagerUi.Init(m_hWnd);
		m_paintManagerUi.AttachDialog(CDialogBuilder().Create(_T("setter.xml"), NULL, NULL, &m_paintManagerUi));
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

void ZYSetter::Notify(TNotifyUI& msg) {
	if (!_tcscmp(msg.sType, _T("windowinit"))) {
		OnCreate();
	}
	else if (!_tcscmp(msg.sType, _T("click"))) {
		if (!_tcscmp(msg.pSender->GetName(), _T("closebutton")) || !_tcscmp(msg.pSender->GetName(), _T("cancelbutton"))) {
			Close();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("okbutton"))) {
			OnSaveButtonClick();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("browsebutton"))) {
			ZYFolderPicker folderpicker(this);
			folderpicker.Create(m_hWnd, _T("ZYFolderPicker"), UI_CLASSSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
			folderpicker.CenterWindow();
			::SetWindowLong(folderpicker, GWL_STYLE, (::GetWindowLong(folderpicker, GWL_STYLE) & ~WS_CAPTION) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
			folderpicker.ShowModal();
		}
	}
}

VOID ZYSetter::OnDir(LPCTSTR dir) {
	CEditUI *edit;
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("downloaddir")))) {
		edit->SetText(dir);
	}
}

VOID ZYSetter::OnCreate() {
	ZYConfigurator *configurator = ZYConfigurator::GetInstance();
	COptionUI *option;
	CEditUI *edit;
	if ((option = (COptionUI *) m_paintManagerUi.FindControl(_T("autostart")))) {
		option->Selected(!_tcscmp(configurator->GetValue(_T("autostart")).GetData(), _T("true")) ? true : false);
	}
	if ((option = (COptionUI *) m_paintManagerUi.FindControl(_T("autodownload")))) {
		option->Selected(!_tcscmp(configurator->GetValue(_T("autodownload")).GetData(), _T("true")) ? true : false);
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("url")))) {
		edit->SetText(configurator->GetValue(_T("url")).GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("downloaddir")))) {
		CStdString dir = configurator->GetValue(_T("downloaddir"));
		edit->SetText(dir.GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("fileext")))) {
		edit->SetText(configurator->GetValue(_T("fileext")).GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("cx")))) {
		edit->SetText(configurator->GetValue(_T("cx")).GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("cy")))) {
		edit->SetText(configurator->GetValue(_T("cy")).GetData());
	}
	if ((option = (COptionUI *) m_paintManagerUi.FindControl(_T("enabletimer")))) {
		option->Selected(!_tcscmp(configurator->GetValue(_T("enabletimer")).GetData(), _T("true")) ? true : false);
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("timerinterval")))) {
		edit->SetText(configurator->GetValue(_T("timerinterval")).GetData());
	}
}

VOID ZYSetter::OnSaveButtonClick() {
	ZYConfigurator *configurator = ZYConfigurator::GetInstance();
	COptionUI *option;
	CEditUI *edit;
	if ((option = (COptionUI *) m_paintManagerUi.FindControl(_T("autostart")))) {
		configurator->SetValue(_T("autostart"), option->IsSelected() ? _T("true") : _T("false"));
	}
	if ((option = (COptionUI *) m_paintManagerUi.FindControl(_T("autodownload")))) {
		configurator->SetValue(_T("autodownload"), option->IsSelected() ? _T("true") : _T("false"));
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("url")))) {
		configurator->SetValue(_T("url"), edit->GetText().GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("downloaddir")))) {
		configurator->SetValue(_T("downloaddir"), edit->GetText().GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("fileext")))) {
		configurator->SetValue(_T("fileext"), edit->GetText().GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("cx")))) {
		configurator->SetValue(_T("cx"), edit->GetText().GetData());
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("cy")))) {
		configurator->SetValue(_T("cy"), edit->GetText().GetData());
	}
	if ((option = (COptionUI *) m_paintManagerUi.FindControl(_T("enabletimer")))) {
		configurator->SetValue(_T("enabletimer"), option->IsSelected() ? _T("true") : _T("false"));
	}
	if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("timerinterval")))) {
		configurator->SetValue(_T("timerinterval"), edit->GetText().GetData());
	}
	Close();
}

LPCTSTR ZYSetter::GetWindowClassName() const {
	return _T("ZYSetter");
}

}