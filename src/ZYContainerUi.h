///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYContainerUi.h
/// @brief 容器控件
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYCONTAINERUI_H_
#define _ZYCONTAINERUI_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// 容器控件
class ZYContainerUi : public CContainerUI {
public:
	/// 绘制背景
	virtual void PaintBkImage(HDC hDC);
};

}

#endif
