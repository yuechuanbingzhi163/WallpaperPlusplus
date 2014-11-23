///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYGroupCreator.h
/// @brief �������鴰��
///
/// @version 1.0
/// @author ������
/// @date 2014��11��23��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYGROUPCREATOR_H_
#define _ZYGROUPCREATOR_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {


/// ��������ص�
class ZYGroupCreatorListener {
public:
	/// ���������¼�
	///
	/// @param groupname ������
	virtual VOID OnGroup(LPCTSTR groupname) = 0;
};

/// �������鴰��
class ZYGroupCreator : public CWindowWnd, public INotifyUI {
public:
	/// ���캯��
	ZYGroupCreator(ZYGroupCreatorListener *cb);

	/// ��Ϣ������
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// �ؼ���Ϣ������
	virtual VOID Notify(TNotifyUI& msg);

	/// ��ȡ��������
	virtual LPCTSTR GetWindowClassName() const;

protected:
	/// ��������ص�
	ZYGroupCreatorListener *m_cb;

	/// ���ڻ�ͼ������
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
