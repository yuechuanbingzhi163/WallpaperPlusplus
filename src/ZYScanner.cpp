///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYScanner.cpp
/// @brief ������
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYScanner.h"
#include "ZYConfigurator.h"

namespace DuiLib {

vector<CStdString> ZYScanner::Scan(LPCTSTR dir, DWORD attribute) {
	WIN32_FIND_DATA findData;
	HANDLE find;
	vector<CStdString> res;
	CStdString _dir;
	_dir.Format(_T("%s%s*.*"), dir, dir[_tcslen(dir) - 1] != _T('\\') ? _T("\\") : _T(""));
	if ((find = ::FindFirstFile(_dir, &findData))) {
		if ((findData.dwFileAttributes & attribute)) {
			res.push_back(findData.cFileName);
		}
		while (::FindNextFile(find, &findData)) {
			if ((findData.dwFileAttributes & attribute)) {
				res.push_back(findData.cFileName);
			}
		}
		FindClose(find);
	}
	return res;
}

}