///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYWallpaperHelper.cpp
/// @brief 壁纸工具
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
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

/// 设置壁纸.壁纸轮换
class ZYWallpaperHelper {
public:
	/// 析构函数
	virtual ~ZYWallpaperHelper();

	/// 设置壁纸
	///
	/// 壁纸是平铺的
	/// @param imagepath 图片路径
	/// @return 返回 TRUE 设置成功, 返回 FALSE 设置失败
	virtual BOOL SetWallpaper(LPCTSTR imagepath);

	/// 获取壁纸工具唯一实例
	///
	/// @return 壁纸工具实例
	static ZYWallpaperHelper *GetInstance();

	/// 图片轮换
	///
	/// 系统定时器 1s 回调
	static VOID WINAPI TimerProc(HWND hWnd, UINT uMsg, UINT_PTR nIDEvent, DWORD dwTime);

protected:
	/// 私有构造函数
	ZYWallpaperHelper();

	/// 桌面组件接口
	IActiveDesktop *m_desktop;
};

}

#endif
