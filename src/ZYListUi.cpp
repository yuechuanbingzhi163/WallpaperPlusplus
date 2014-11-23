///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYListUi.cpp
/// @brief 表格控件
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYListUi.h"

namespace DuiLib {

ZYListUi::ZYListUi() : m_index(0) {
	m_list.nColumns = 0;
	m_list.nFont = -1;
	m_list.uTextStyle = DT_VCENTER;
	m_list.dwTextColor = 0xFF000000;
	m_list.dwBkColor = 0;
	m_list.bAlternateBk = false;
	m_list.dwSelectedTextColor = 0xFF000000;
	m_list.dwSelectedBkColor = 0;
	m_list.dwHotTextColor = 0xFF000000;
	m_list.dwHotBkColor = 0;
	m_list.dwDisabledTextColor = 0xFFCCCCCC;
	m_list.dwDisabledBkColor = 0xFFFFFFFF;
	m_list.dwLineColor = 0;
	m_list.bShowHtml = false;
	m_list.bMultiExpandable = false;
	::ZeroMemory(&m_list.rcTextPadding, sizeof(m_list.rcTextPadding));
    ::ZeroMemory(&m_list.rcColumn, sizeof(m_list.rcColumn));
}

LPCTSTR ZYListUi::GetClass() const {
    return _T("ZYListUi");
}

LPVOID ZYListUi::GetInterface(LPCTSTR pstrName) {
	if(!_tcscmp(pstrName, _T("IListOwner"))) return static_cast<IListOwnerUI *>(this);
	return CTileLayoutUI::GetInterface(pstrName);
}

TListInfoUI* ZYListUi::GetListInfo() {
	return &m_list;
}

bool ZYListUi::Add(CControlUI* control) {
	if (!CTileLayoutUI::Add(control)) {
		return false;
	}
	IListItemUI* listItemUi = (IListItemUI*) control->GetInterface(_T("ListItem"));
	if(listItemUi != NULL) {
		listItemUi->SetOwner(this);
		listItemUi->SetIndex(m_items.GetSize());
	};
	m_index =-1;
	return true;
}

bool ZYListUi::AddAt(CControlUI* control, int index) {
	if (!CTileLayoutUI::AddAt(control, index)) {
		return false;
	}
	IListItemUI* listItemUi = (IListItemUI*) control->GetInterface(_T("ListItem"));
	if(listItemUi != NULL) {
		listItemUi->SetOwner(this);
		listItemUi->SetIndex(m_items.GetSize());
	}
	m_index =-1;
	return true;
}

bool ZYListUi::Remove(CControlUI* control) {
	int index = GetItemIndex(control);
	if (0 <= index) {
		return RemoveAt(index);
	}
	return false;
}

bool ZYListUi::RemoveAt(int index) {
	if (CTileLayoutUI::RemoveAt(index)) {
		return false;
	}
	for(int i = index; i < GetCount(); ++i) {
		CControlUI* control = GetItemAt(i);
		IListItemUI* listItemUi = (IListItemUI*) control->GetInterface(_T("ListItem"));
		if(listItemUi != NULL) listItemUi->SetIndex(i);
	}
	m_index =-1;
	return true;
}

INT ZYListUi::GetCurSel() const {
	return m_index;
}

bool ZYListUi::SelectItem(int index) {
	CControlUI* control;
	if (0 <= m_index && (control = GetItemAt(m_index))) {
		IListItemUI* listItemUi;
		if (listItemUi = (IListItemUI*) control->GetInterface(_T("ListItem"))) {
			listItemUi->Select(false);
			m_index = -1;
		}
	}
	if (index-- < 0) return false;
	if((control = GetItemAt(index))) {
		IListItemUI* listItemUi;
		if ((listItemUi = (IListItemUI*) control->GetInterface(_T("ListItem")))) {
			m_index = index;
			if (!listItemUi->Select(true)) return false;
		}
	}
	if(m_pManager) m_pManager->SendNotify(this, _T("itemselect"), m_index);
	return true;
}

VOID ZYListUi::DoEvent(TEventUI &event) {
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
		if(m_pParent) m_pParent->DoEvent(event); else CTileLayoutUI::DoEvent(event);
		return;
	}
	CTileLayoutUI::DoEvent(event);
}

}