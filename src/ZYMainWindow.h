///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYMainWindow.h
/// @brief ������
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
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

/// ������
class ZYMainWindow : public CWindowWnd, public INotifyUI, IDialogBuilderCallback, ZYFolderPickerListener, ZYGroupCreatorListener, ZYImageSnifferListener {
public:
	/// ���캯��
	ZYMainWindow();

	/// ��������
	~ZYMainWindow();

	/// �����Զ���ؼ�
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	
	/// ��Ϣ������
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// �ؼ���Ϣ������
	virtual VOID Notify(TNotifyUI& msg);

	/// ��ȡ��������
	virtual LPCTSTR GetWindowClassName() const;

	/// ѡ��Ŀ¼�¼�
	///
	/// @param dir Ŀ¼
	virtual VOID OnDir(LPCTSTR dir);

	/// ���������¼�
	///
	/// @param groupname ������
	virtual VOID OnGroup(LPCTSTR groupname);

	/// ���ȸı��¼�
	///
	/// @param progress ��ǰ����
	virtual VOID OnProgress(LONG progress);

protected:
	/// ���ڴ����¼�
	virtual VOID OnCreate();

	/// ��ӷ��鰴ť����¼�
	virtual VOID OnAddGroupButtonClick();

	/// ɾ�����鰴ť����¼�
	virtual VOID OnDeleteGroupButtonClick();

	/// Ӧ�ð�ť����¼�
	virtual VOID OnApplyButtonClick();

	/// ���밴ť����¼�
	virtual VOID OnImportButtonClick();

	/// ���ð�ť����¼�
	virtual VOID OnConfigureButtonClick();

	/// ���ذ�ť����¼�
	virtual VOID OnDownloadButtonClick();
	
	/// ���ز�ѡ�з���
	///
	/// @param groupname ��������
	virtual VOID LoadGroupsAndSelect(LPCTSTR groupname);

	/// ����ָ������ͼƬ
	///
	/// @param groupid ������
	virtual VOID LoadItemsByGroupid(LPCTSTR groupid);

	/// ���ͼƬ
	///
	/// @param filepath �ļ�λ��
	virtual VOID AddItem(LPCTSTR filepath);

	/// ����ͼƬѡ��
	///
	/// @param select TRUE ѡ������, FALSE ȡ������
	virtual VOID SetSelectForAllItems(BOOL select);

	/// ��̽��
	ZYImageSniffer *m_imageSniffer;

	/// �б�ؼ�
	ZYListUi *m_list;

	/// ��Ͽ�ؼ�
	CComboUI *m_combobox;

	/// ���ڻ�ͼ������
	CPaintManagerUI m_paintManagerUi;
};

}

#endif
