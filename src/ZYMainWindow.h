///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYMainWindow.h
/// @brief 主窗口
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYMAINWINDOW_H_
#define _ZYMAINWINDOW_H_

#include "ZYFolderPicker.h"
#include "ZYGroupCreator.h"
#include "ZYImageSniffer.h"
#include "ZYListUi.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// 主窗口
class ZYMainWindow : public CWindowWnd, public INotifyUI, IDialogBuilderCallback, ZYFolderPickerListener, ZYGroupCreatorListener, ZYImageSnifferListener {
public:
	/// 构造函数
	ZYMainWindow();

	/// 析构函数
	~ZYMainWindow();

	/// 创建自定义控件
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	
	/// 消息处理函数
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// 控件消息处理函数
	virtual VOID Notify(TNotifyUI& msg);

	/// 获取窗口类名
	virtual LPCTSTR GetWindowClassName() const;

	/// 选中目录事件
	///
	/// @param dir 目录
	virtual VOID OnDir(LPCTSTR dir);

	/// 创建分组事件
	///
	/// @param groupname 分组名
	virtual VOID OnGroup(LPCTSTR groupname);

	/// 进度改变事件
	///
	/// @param progress 当前进度
	virtual VOID OnProgress(LONG progress);

protected:
	/// 窗口创建事件
	virtual VOID OnCreate();

	/// 添加分组按钮点击事件
	virtual VOID OnAddGroupButtonClick();

	/// 删除分组按钮点击事件
	virtual VOID OnDeleteGroupButtonClick();

	/// 应用按钮点击事件
	virtual VOID OnApplyButtonClick();

	/// 导入按钮点击事件
	virtual VOID OnImportButtonClick();

	/// 设置按钮点击事件
	virtual VOID OnConfigureButtonClick();

	/// 下载按钮点击事件
	virtual VOID OnDownloadButtonClick();
	
	/// 加载并选中分组
	///
	/// @param groupname 分组名称
	virtual VOID LoadGroupsAndSelect(LPCTSTR groupname);

	/// 加载指定分组图片
	///
	/// @param groupid 分组编号
	virtual VOID LoadItemsByGroupid(LPCTSTR groupid);

	/// 添加图片
	///
	/// @param filepath 文件位置
	virtual VOID AddItem(LPCTSTR filepath);

	/// 设置图片选中
	///
	/// @param select TRUE 选中所有, FALSE 取消所有
	virtual VOID SetSelectForAllItems(BOOL select);

	/// 嗅探器
	ZYImageSniffer *m_imageSniffer;

	/// 列表控件
	ZYListUi *m_list;

	/// 组合框控件
	CComboUI *m_combobox;

	/// 窗口绘图管理器
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
