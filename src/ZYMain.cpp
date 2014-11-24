///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYMain.cpp
/// @brief 主程序
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYMainWindow.h"
#include "ZYConfigurator.h"
#include "ZYWallpaperHelper.h"
#include "../include/DuiLib/UIlib.h"

using namespace DuiLib;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (FindWindow(NULL, _T("ZYMainWindow"))) {
		return 0;
	}
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourceZip(_T("Wallpaper++.zip"));
	ZYConfigurator *configurator = ZYConfigurator::GetInstance();
	ZYMainWindow mainWindow;
	mainWindow.Create(NULL, _T("ZYMainWindow"), UI_WNDSTYLE_DIALOG, 0, 0, 0, 550, 400);
	mainWindow.CenterWindow();
	::SetWindowLong(mainWindow, GWL_STYLE, (::GetWindowLong(mainWindow, GWL_STYLE) & ~WS_CAPTION) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	mainWindow.ShowWindow(_tcscmp(configurator->GetValue(_T("minimized")).GetData(), _T("true")) ? false : true);
	ZYWallpaperHelper::GetInstance();
	CPaintManagerUI::MessageLoop();
	return 0;
}
