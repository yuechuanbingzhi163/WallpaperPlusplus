///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYSetter.h
/// @brief 设置窗口
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月23日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYSETTER_H_
#define _ZYSETTER_H_

#include "ZYFolderPicker.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// 设置窗口
class ZYSetter : public CWindowWnd, public INotifyUI, ZYFolderPickerListener {
public:
	/// 消息处理函数
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// 控件消息处理函数
	virtual VOID Notify(TNotifyUI& msg);

	/// 获取窗口类名
	virtual LPCTSTR GetWindowClassName() const;

	/// 选中目录事件
	///
	/// @param dir 目录
	/// @param flag 1 为搜索子目录
	virtual VOID OnDir(LPCTSTR dir);

protected:
	/// 窗口创建事件
	virtual VOID OnCreate();

	/// 保存按钮点击事件
	virtual VOID OnSaveButtonClick();

	/// 窗口绘图管理器
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
