///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYScanner.h
/// @brief 搜索器
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////


#ifndef _ZYSCANNER_H_
#define _ZYSCANNER_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <vector>

using namespace std;

namespace DuiLib {

/// 搜索器
class ZYScanner {
public:
	/// 搜索
	///
	/// @param dir 搜索目录
	/// @param attribute 文件属性
	/// @return 在当前目录中搜索结果的集合
	virtual vector<CStdString> Scan(LPCTSTR dir, DWORD attribute);
};

}

#endif
