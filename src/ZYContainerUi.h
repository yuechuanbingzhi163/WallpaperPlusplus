///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYContainerUi.h
/// @brief �����ؼ�
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYCONTAINERUI_H_
#define _ZYCONTAINERUI_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// �����ؼ�
class ZYContainerUi : public CContainerUI {
public:
	/// ���Ʊ���
	virtual void PaintBkImage(HDC hDC);
};

}

#endif
