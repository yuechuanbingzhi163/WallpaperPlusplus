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

#include "ZYDbHelper.h"

namespace DuiLib {

ZYDbHelper::~ZYDbHelper() {
	if (m_db) sqlite3_close(m_db);
}

BOOL ZYDbHelper::Query(LPCTSTR sql, vector<vector<CStdString>> *qset) {
	CHAR _sql[PATH_MAX];
	int len;
	vector<vector<CStdString>> res;
	if (m_db && (len = ::WideCharToMultiByte(CP_ACP, 0, sql, _tcslen(sql), _sql, PATH_MAX, NULL, NULL))) {
		_sql[len] = '\0';
		if (SQLITE_OK == sqlite3_exec(m_db, _sql, ZYDbHelper::GetData, qset, NULL)) {
			return TRUE;
		}
	}
	return FALSE;
}

ZYDbHelper *ZYDbHelper::GetInstance() {
	static ZYDbHelper dbHelper;
	return &dbHelper;
}

ZYDbHelper::ZYDbHelper() : m_db(NULL) {
	CHAR filepath[PATH_MAX];
	LONG len;
	CStdString _filepath;
	_filepath.Format(_T("%s\\Wallpaper++.db"), CPaintManagerUI::GetCurrentPath());
	if ((len = ::WideCharToMultiByte(CP_OEMCP, 0, _filepath.GetData(), _filepath.GetLength(), filepath, PATH_MAX, NULL, NULL))) {
		filepath[len] = '\0';
		if (SQLITE_OK != ::sqlite3_open_v2(filepath, &m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
			if (SQLITE_OK != ::sqlite3_open_v2("Wallpaper++.db", &m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
				m_db = NULL;
			}
		}
	}
}

INT ZYDbHelper::GetData(LPVOID qset, INT count, LPSTR *column, LPSTR *name) {
	if (!qset) {
		return SQLITE_OK;
	}
	TCHAR _column[PATH_MAX];
	LONG len;
	vector<CStdString> row;
	for (int i = 0; i < count; i++) {
		if (column[i] && (len = ::MultiByteToWideChar(CP_OEMCP, 0, column[i], strlen(column[i]), _column, PATH_MAX))) {
			_column[len] = '\0';
			row.push_back(_column);
			continue;
		}
		row.push_back(_T(""));
	}
	((vector<vector<CStdString>> *) qset)->push_back(row);
	return SQLITE_OK;
}

}
