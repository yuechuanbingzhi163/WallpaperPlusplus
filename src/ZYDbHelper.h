///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYDbHelper.cpp
/// @brief 数据库工具
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYDBHELPER_H_
#define _ZYDBHELPER_H_

#include "../include/DuiLib/UIlib.h"
#include "../include/sqlite3.h"
#include <Windows.h>
#include <vector>

using namespace std;

namespace DuiLib {

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

/// 数据库操作接口
class ZYDbHelper {
public:
	/// 析构函数
	virtual ~ZYDbHelper();

	/// SQL 查询
	///
	/// @param sql SQL 查询语句
	/// @param qset 查询数据
	/// @return 返回 TRUE 查询成功, 返回 FALSE 查询失败
	virtual BOOL Query(LPCTSTR sql, vector<vector<CStdString>> *qset);

	/// 获取数据库操作接口唯一实例
	///
	/// @return 数据库操作接口实例
	static ZYDbHelper *GetInstance();

protected:
	/// 私有构造函数
	ZYDbHelper();

	/// 数据库查询结果回调
	static INT GetData(LPVOID qset, INT count, LPSTR *column, LPSTR *name);

	/// 数据库句柄
	sqlite3 *m_db;
};

}

#endif
