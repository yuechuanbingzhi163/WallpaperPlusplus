///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYConfigurator.cpp
/// @brief 配置器
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYCONFIGURATOR_H_
#define _ZYCONFIGURATOR_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <map>

using namespace std;

namespace DuiLib {

/// 配置器
class ZYConfigurator {
public:
	/// 析构函数
	virtual ~ZYConfigurator();

	/// 获取配置
	///
	/// @param key 配置名称
	/// @return 配置
	virtual CStdString GetValue(LPCTSTR key);

	/// 设置配置
	///
	/// @param key 配置名称
	/// @param value 配置
	virtual VOID SetValue(LPCTSTR key, LPCTSTR value);

	/// 获取配置器唯一实例
	///
	/// @return 配置器实例
	static ZYConfigurator *GetInstance();

protected:
	/// 私有构造函数
	ZYConfigurator();

	/// 载入的配置
	map<CStdString, CStdString> m_configs;
};

}

#endif
