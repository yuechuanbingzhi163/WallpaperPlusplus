///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYWallpaperHelper.cpp
/// @brief ��ֽ����
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYWALLPAPERHELPER_H_
#define _ZYWALLPAPERHELPER_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <WinInet.h>
#include <ShlObj.h>
#include <vector>

using namespace std;

namespace DuiLib {

/// ���ñ�ֽ.��ֽ�ֻ�
class ZYWallpaperHelper {
public:
	/// ��������
	virtual ~ZYWallpaperHelper();

	/// ���ñ�ֽ
	///
	/// ��ֽ��ƽ�̵�
	/// @param imagepath ͼƬ·��
	/// @return ���� TRUE ���óɹ�, ���� FALSE ����ʧ��
	virtual BOOL SetWallpaper(LPCTSTR imagepath);

	/// ��ȡ��ֽ����Ψһʵ��
	///
	/// @return ��ֽ����ʵ��
	static ZYWallpaperHelper *GetInstance();

	/// ͼƬ�ֻ�
	///
	/// ϵͳ��ʱ�� 1s �ص�
	static VOID WINAPI TimerProc(HWND hWnd, UINT uMsg, UINT_PTR nIDEvent, DWORD dwTime);

protected:
	/// ˽�й��캯��
	ZYWallpaperHelper();

	/// ��������ӿ�
	IActiveDesktop *m_desktop;
};

}

#endif
