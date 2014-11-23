///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYListUi.h
/// @brief ���ؼ�
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYLISTUI_H_
#define _ZYLISTUI_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

class ZYListUi : public CTileLayoutUI, public IListOwnerUI {
public:
	/// ���캯��
	ZYListUi();
	
	/// ��ȡ����
	virtual LPCTSTR GetClass() const;

	/// ��ȡ�ӿ�
	virtual LPVOID GetInterface(LPCTSTR pstrName);

	/// ���Ԫ��
	virtual bool Add(CControlUI* control);

	/// ��ָ��λ�����Ԫ��
	virtual bool AddAt(CControlUI* control, int index);

	/// ɾ��Ԫ��
	virtual bool Remove(CControlUI* control);

	/// ɾ��ָ��λ�ô���Ԫ��
	virtual bool RemoveAt(int index);

	/// ��ȡ�б���Ϣ
	virtual TListInfoUI* GetListInfo();

	/// ��ȡѡ����
	virtual int GetCurSel() const;

	/// ѡ��Ԫ��
	virtual bool SelectItem(int index);

	/// �����¼�
	virtual void DoEvent(TEventUI &event);

protected:
	/// ѡ��������
	INT m_index;

	/// �б���Ϣ
	TListInfoUI m_list;
};

}

#endif
