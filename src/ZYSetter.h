///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYSetter.h
/// @brief ���ô���
///
/// @version 1.0
/// @author ������
/// @date 2014��11��23��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYSETTER_H_
#define _ZYSETTER_H_

#include "ZYFolderPicker.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// ���ô���
class ZYSetter : public CWindowWnd, public INotifyUI, ZYFolderPickerListener {
public:
	/// ��Ϣ������
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// �ؼ���Ϣ������
	virtual VOID Notify(TNotifyUI& msg);

	/// ��ȡ��������
	virtual LPCTSTR GetWindowClassName() const;

	/// ѡ��Ŀ¼�¼�
	///
	/// @param dir Ŀ¼
	/// @param flag 1 Ϊ������Ŀ¼
	virtual VOID OnDir(LPCTSTR dir);

protected:
	/// ���ڴ����¼�
	virtual VOID OnCreate();

	/// ���水ť����¼�
	virtual VOID OnSaveButtonClick();

	/// ���ڻ�ͼ������
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
