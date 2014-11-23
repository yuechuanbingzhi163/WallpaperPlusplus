///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYListUi.cpp
/// @brief ���ؼ�
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYContainerUi.h"

namespace DuiLib {

void ZYContainerUi::PaintBkImage(HDC hDC) {
	if(!m_sBkImage.IsEmpty()) {
		CStdString olddir = CPaintManagerUI::GetResourceZip();
		CPaintManagerUI::SetResourceZip(_T(""));
		LONG pos = m_sBkImage.ReverseFind(_T('\\'));
		CPaintManagerUI::SetResourcePath(m_sBkImage.Left(pos).GetData());
		if (!DrawImage(hDC, m_sBkImage.Mid(pos).GetData())) {
			m_sBkImage.Empty();
		}
		CPaintManagerUI::SetResourceZip(olddir.GetData());
	}
}

}