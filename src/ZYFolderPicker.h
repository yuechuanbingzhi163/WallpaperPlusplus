///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYFolderPicker.cpp
/// @brief 选择文件夹
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYFOLDERPICKER_H_
#define _ZYFOLDERPICKER_H_

#include "ZYScanner.h"

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

/// 选择文件夹回调
class ZYFolderPickerListener {
public:
	/// 选中目录事件
	///
	/// @param dir 目录
	virtual VOID OnDir(LPCTSTR dir) = 0;
};

/// 选择文件夹窗口
class ZYFolderPicker : public CWindowWnd, public INotifyUI {
public:
	/// 构造函数
	ZYFolderPicker(ZYFolderPickerListener *cb);

	/// 消息处理函数
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// 控件消息处理函数
	virtual VOID Notify(TNotifyUI& msg);

	/// 获取窗口类名
	virtual LPCTSTR GetWindowClassName() const;

protected:
	/// 窗口创建事件
	virtual VOID OnCreate();

	/// 搜索子目录
	///
	/// @param dir 搜索目录
	virtual VOID LoadItems(LPCTSTR dir);

	/// 添加目录
	///
	/// @param foldername 文件夹名称
	virtual VOID AddItem(LPCTSTR foldername);

	/// 目录选中事件
	virtual VOID OnItemSelect();

	/// 选择文件夹回调
	ZYFolderPickerListener *m_cb;

	/// 当前目录
	CStdString m_dir;

	/// 列表控件
	CListUI *m_list;

	/// 窗口绘图管理器
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
