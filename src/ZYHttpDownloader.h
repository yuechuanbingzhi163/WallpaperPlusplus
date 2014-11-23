///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYHttpDownloader.h
/// @brief ������
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYHTTPDOWNLOADER_H_
#define _ZYHTTPDOWNLOADER_H_

#include "ZYScanner.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <vector>

using namespace std;

namespace DuiLib {

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

/// ���ػص�
class ZYHttpDownloaderListener {
public:
	/// ��������¼�
	///
	/// @param url ���ص�ַ
	/// @param fileparh �ļ�λ��
	virtual VOID OnComplete(LPCTSTR url, LPCTSTR filepath) = 0;

	/// ����ʧ���¼�
	///
	/// @param url ���ص�ַ
	virtual VOID OnError(LPCTSTR url) = 0;
};

/// ������
class ZYHttpDownloader {
public:
	/// ���캯��
	///
	/// @param cb ���ػص�
	ZYHttpDownloader(ZYHttpDownloaderListener *cb);

	/// ��������
	virtual ~ZYHttpDownloader();

	/// �����������
	///
	/// @param url ���ص�ַ
	/// @return ���� TRUE ��ӳɹ�, ���� FALSE ���ʧ��
	virtual BOOL Download(LPCTSTR url);

	/// ������ض���
	virtual VOID Reset();

	/// ��ȡ������������
	///
	/// @return ����
	virtual LONG GetUrlsSize();

	/// ��ȡ�ļ���
	///
	/// @param url ���ص�ַ
	/// @return �ļ���
	static CStdString GetFilename(LPCTSTR url);
	
	/// �����߳�
	///
	/// @param thiz ��ʼ������
	/// @return �߳̽��
	static DWORD WINAPI DownloadThread(LPVOID thiz);

protected:
	/// �����ض����л�ȡһ�����ص�ַ
	///
	/// @return ���ص�ַ
	virtual CStdString GetUrl();

	/// �����ļ���
	///
	/// @param dir Ŀ¼
	/// @param filename �ļ���
	/// @return �������ļ���
	virtual CStdString FixFilename(LPCTSTR dir, LPCTSTR filename);

	/// ���ػص�
	ZYHttpDownloaderListener *m_cb;

	/// ���ض���
	vector<CStdString> m_urls;

	/// �߳̿��Ʊ�ʶ
	BOOL m_run;

	/// �߳̾��
	HANDLE m_thread;

	/// �ڴ���ʻ�����
	HANDLE m_mutex;
};

}

#endif
