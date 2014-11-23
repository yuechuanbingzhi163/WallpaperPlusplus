///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYGroupCreator.h
/// @brief 创建分组窗口
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月23日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYGROUPCREATOR_H_
#define _ZYGROUPCREATOR_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {


/// 创建分组回调
class ZYGroupCreatorListener {
public:
	/// 创建分组事件
	///
	/// @param groupname 分组名
	virtual VOID OnGroup(LPCTSTR groupname) = 0;
};

/// 创建分组窗口
class ZYGroupCreator : public CWindowWnd, public INotifyUI {
public:
	/// 构造函数
	ZYGroupCreator(ZYGroupCreatorListener *cb);

	/// 消息处理函数
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// 控件消息处理函数
	virtual VOID Notify(TNotifyUI& msg);

	/// 获取窗口类名
	virtual LPCTSTR GetWindowClassName() const;

protected:
	/// 创建分组回调
	ZYGroupCreatorListener *m_cb;

	/// 窗口绘图管理器
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
