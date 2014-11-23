///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYImageSniffer.h
/// @brief ��̽��
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYIMAGESNIFFER_H_
#define _ZYIMAGESNIFFER_H_

#include "ZYHttpDownloader.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// ��̽���ص�
class ZYImageSnifferListener {
public:
	/// ���ȸı��¼�
	///
	/// @param progress ��ǰ����
	virtual VOID OnProgress(LONG progress) = 0;
};

/// ��̽��
class ZYImageSniffer : public ZYHttpDownloaderListener {
public:
	/// ���캯��
	///
	/// @param cb ��̽���ص�
	ZYImageSniffer(ZYImageSnifferListener *cb);

	/// ��������
	~ZYImageSniffer();

	/// ��ȡ�ƶ�ҳ���е�ͼƬ
	///
	/// @param url ҳ���ַ
	/// @return ���� TRUE ��ʼ��ȡ, ���� FALSE ��ǰ�����������
	virtual BOOL Sniff(LPCTSTR url);
	
	/// ��������¼�
	///
	/// @param url ���ص�ַ
	/// @param fileparh �ļ�λ��
	virtual VOID OnComplete(LPCTSTR url, LPCTSTR filepath);

	/// ����ʧ���¼�
	/// @param url ���ص�ַ
	virtual VOID OnError(LPCTSTR url);

	/// ����ļ���׺
	///
	/// ͨ��ͬ�������еĺ�׺�Ƚϼ���Ƿ�ΪͼƬ��ʽ
	/// @param filename �ļ���
	/// @return ���� TRUE ��ͼƬ, ���� FALSE����ͼƬ
	static BOOL CheckFileextension(LPCTSTR filename);

	/// ���ͼ���С
	///
	/// ͨ��ͬ�������е���СͼƬ��С�ж��Ƿ���ϱ�ֽ��С
	/// @param filepath �ļ�λ��
	/// @return ���� TRUE ���ϴ�С, ���� FALSE����
	static BOOL CheckImageSize(LPCTSTR filepath);

protected:
	/// ���ļ��л�ȡͼƬ url
	///
	/// @param filepath �ļ�·��
	/// @return ͼƬ��ַ
	virtual vector<CStdString> GetImageUrls(LPCTSTR filepath);

	/// ��ǰ״̬
	DWORD m_state;

	/// ͼƬ����
	LONG m_size;

	/// ��̽���ص�
	ZYImageSnifferListener *m_cb;

	/// ������
	ZYHttpDownloader *m_httpDownloader;
};

}

#endif
