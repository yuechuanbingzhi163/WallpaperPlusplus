///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYScanner.cpp
/// @brief 搜索器
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYWallpaperHelper.h"
#include "ZYConfigurator.h"
#include "ZYDbHelper.h"

namespace DuiLib {

ZYWallpaperHelper::~ZYWallpaperHelper() {
	::KillTimer(NULL, 1);
	if (m_desktop) {
		m_desktop->Release();
	}
	::CoUninitialize();
}

BOOL ZYWallpaperHelper::SetWallpaper(LPCTSTR imagepath) {
	WALLPAPEROPT wpo;
	wpo.dwSize = sizeof(WALLPAPEROPT);
	wpo.dwStyle = WPSTYLE_STRETCH;
	if (m_desktop && S_OK == m_desktop->SetWallpaperOptions(&wpo, 0) && S_OK == m_desktop->SetWallpaper(imagepath, 0)) {
		if (S_OK == m_desktop->ApplyChanges(AD_APPLY_ALL | AD_APPLY_FORCE)) {
			return TRUE;
		}
	}
	return FALSE;
}

ZYWallpaperHelper *ZYWallpaperHelper::GetInstance() {
	static ZYWallpaperHelper wallpaperHelper;
	return &wallpaperHelper;
}

ZYWallpaperHelper::ZYWallpaperHelper() : m_desktop(NULL) {
	::CoInitialize(NULL);
	::CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, IID_IActiveDesktop, (void**)&m_desktop);
	::SetTimer(NULL, 1, 1000, ZYWallpaperHelper::TimerProc);
}

VOID WINAPI ZYWallpaperHelper::TimerProc(HWND hWnd, UINT uMsg, UINT_PTR nIDEvent, DWORD dwTime) {
	ZYConfigurator *configurator = ZYConfigurator::GetInstance();
	static ULONG tick;
	static ULONG curr;
	if (!_tcscmp(configurator->GetValue(_T("enabletimer")), _T("true"))) {
		if (++tick == ::_ttoi(configurator->GetValue(_T("timerinterval")))) {
			CStdString groupid = configurator->GetValue(_T("groupid"));
			if (groupid.IsEmpty()) {
				groupid = _T("1");
			}
			CStdString sql;
			vector<vector<CStdString>> qset;
			sql.Format(_T("SELECT path FROM `wallpaper` WHERE groupid=%s; "), groupid.GetData());
			if (ZYDbHelper::GetInstance()->Query(sql.GetData(), &qset)) {
					if (!qset.empty()) {
					if (qset.size() <= curr) {
						curr = 0;
					}
					ZYWallpaperHelper::GetInstance()->SetWallpaper(qset[curr++][0].GetData());
				}
				
			}
			tick = 0;
		}
	}
}

}
