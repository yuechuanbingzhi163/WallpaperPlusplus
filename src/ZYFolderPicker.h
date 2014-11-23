///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYFolderPicker.cpp
/// @brief ѡ���ļ���
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
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

/// ѡ���ļ��лص�
class ZYFolderPickerListener {
public:
	/// ѡ��Ŀ¼�¼�
	///
	/// @param dir Ŀ¼
	virtual VOID OnDir(LPCTSTR dir) = 0;
};

/// ѡ���ļ��д���
class ZYFolderPicker : public CWindowWnd, public INotifyUI {
public:
	/// ���캯��
	ZYFolderPicker(ZYFolderPickerListener *cb);

	/// ��Ϣ������
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// �ؼ���Ϣ������
	virtual VOID Notify(TNotifyUI& msg);

	/// ��ȡ��������
	virtual LPCTSTR GetWindowClassName() const;

protected:
	/// ���ڴ����¼�
	virtual VOID OnCreate();

	/// ������Ŀ¼
	///
	/// @param dir ����Ŀ¼
	virtual VOID LoadItems(LPCTSTR dir);

	/// ���Ŀ¼
	///
	/// @param foldername �ļ�������
	virtual VOID AddItem(LPCTSTR foldername);

	/// Ŀ¼ѡ���¼�
	virtual VOID OnItemSelect();

	/// ѡ���ļ��лص�
	ZYFolderPickerListener *m_cb;

	/// ��ǰĿ¼
	CStdString m_dir;

	/// �б�ؼ�
	CListUI *m_list;

	/// ���ڻ�ͼ������
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
