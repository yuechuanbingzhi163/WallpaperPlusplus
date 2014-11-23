///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYListUi.h
/// @brief 表格控件
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYLISTUI_H_
#define _ZYLISTUI_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

class ZYListUi : public CTileLayoutUI, public IListOwnerUI {
public:
	/// 构造函数
	ZYListUi();
	
	/// 获取类名
	virtual LPCTSTR GetClass() const;

	/// 获取接口
	virtual LPVOID GetInterface(LPCTSTR pstrName);

	/// 添加元素
	virtual bool Add(CControlUI* control);

	/// 在指定位置添加元素
	virtual bool AddAt(CControlUI* control, int index);

	/// 删除元素
	virtual bool Remove(CControlUI* control);

	/// 删除指定位置处的元素
	virtual bool RemoveAt(int index);

	/// 获取列表信息
	virtual TListInfoUI* GetListInfo();

	/// 获取选中项
	virtual int GetCurSel() const;

	/// 选择元素
	virtual bool SelectItem(int index);

	/// 处理事件
	virtual void DoEvent(TEventUI &event);

protected:
	/// 选中项索引
	INT m_index;

	/// 列表信息
	TListInfoUI m_list;
};

}

#endif
