///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYGroupCreator.cpp
/// @brief 创建分组窗口
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月23日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYGroupCreator.h"
#include "ZYDbHelper.h"

namespace DuiLib {

ZYGroupCreator::ZYGroupCreator(ZYGroupCreatorListener *cb) :m_cb(cb) {
}

LRESULT ZYGroupCreator::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (WM_CREATE == uMsg) {
		m_paintManagerUi.Init(m_hWnd);
		m_paintManagerUi.AttachDialog(CDialogBuilder().Create(_T("groupcreator.xml"), NULL, NULL, &m_paintManagerUi));
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

void ZYGroupCreator::Notify(TNotifyUI& msg) {
	if (!_tcscmp(msg.sType, _T("windowinit"))) {
		::SetWindowLong(m_hWnd, GWL_STYLE, ::GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	}
	else if (!_tcscmp(msg.sType, _T("click"))) {
		if (!_tcscmp(msg.pSender->GetName(), _T("closebutton")) || !_tcscmp(msg.pSender->GetName(), _T("cancelbutton"))) {
			Close();
		} else if (!_tcscmp(msg.pSender->GetName(), _T("okbutton"))) {
			CEditUI *edit;
			if ((edit = (CEditUI *) m_paintManagerUi.FindControl(_T("groupname")))) {
				CStdString sql;
				CStdString groupname = edit->GetText();
				if (!groupname.IsEmpty()) {
					sql.Format(_T("INSERT INTO `group` (name) VALUES ('%s'); "), groupname.GetData());
					if (ZYDbHelper::GetInstance()->Query(sql.GetData(), NULL)) {
						if (m_cb) {
							m_cb->OnGroup(groupname.GetData());
						}
						Close();
					}
				}
			}
		}
	}
}

LPCTSTR ZYGroupCreator::GetWindowClassName() const {
	return _T("ZYGroupCreator");
}

}