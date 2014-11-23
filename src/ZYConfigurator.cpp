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

#include "ZYConfigurator.h"
#include "ZYDbHelper.h"

namespace DuiLib {

static LPCTSTR s_table[] = {
	_T("CREATE TABLE IF NOT EXISTS `wallpaper` (`path` VARCHAR(512), `groupid` INTEGER, CONSTRAINT id PRIMARY KEY (`path`, `groupid`)); "),
	_T("CREATE TABLE IF NOT EXISTS `group` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` VARCHAR(512)); "),
	_T("CREATE TABLE IF NOT EXISTS `config` (`key` VARCHAR(256), `value` VARCHAR(256)); "),

	_T("INSERT INTO `group` VALUES(1, '默认'); ")
};

static LPCTSTR s_configs[][2] = {
	{_T("autostart"), _T("")},
	{_T("autodownload"), _T("")},
	{_T("url"), _T("http://cn.bing.com/")},
	{_T("fileext"), _T(".bmp,.jpg,.png")},
	{_T("cx"), _T("800")},
	{_T("cy"), _T("600")},
	{_T("timerinterval"), _T("1200")},
	{_T("enabletimer"), _T("false")}
};

ZYConfigurator::~ZYConfigurator() {
	ZYDbHelper *dbHelper = ZYDbHelper::GetInstance();
	dbHelper->Query(_T("DELETE FROM `config`; "), NULL);
	for(map<CStdString, CStdString>::iterator it = m_configs.begin(); it != m_configs.end(); it++) {
		CStdString sql;
		sql += _T("INSERT INTO `config` VALUES ('");
		sql += (*it).first;
		sql += _T("', '");
		sql += (*it).second;
		sql += _T("'); ");
		dbHelper->Query(sql, NULL);
	}
}

CStdString ZYConfigurator::GetValue(LPCTSTR key) {
	if (m_configs.find(key) != m_configs.end()) {
		return m_configs[key];
	}
	return _T("");
}

VOID ZYConfigurator::SetValue(LPCTSTR key, LPCTSTR value) {
	m_configs[key] = value;
}

ZYConfigurator *ZYConfigurator::GetInstance() {
	static ZYConfigurator configurator;
	return &configurator;
}

ZYConfigurator::ZYConfigurator() {
	ZYDbHelper *dbHelper = ZYDbHelper::GetInstance();
	for (int i = 0; i < sizeof(s_table) / sizeof(s_table[0]); i++) {
		dbHelper->Query(s_table[i], NULL);
	}
	vector<vector<CStdString>> qset;
	dbHelper->Query(_T("SELECT `key`, `value` FROM `config`; "), &qset);
	for (vector<vector<CStdString>>::iterator it = qset.begin(); it != qset.end(); it++) {
		vector<CStdString> &v = *it;
		m_configs[*v.begin()] = *(v.begin() + 1);
	}
	if (GetValue(_T("downloaddir")).IsEmpty()) {
		SetValue(_T("downloaddir"), CPaintManagerUI::GetCurrentPath());
	}
	for (int i = 0; i < sizeof(s_configs) / sizeof(s_configs[0]); i++) {
		if (GetValue(s_configs[i][0]).IsEmpty()) {
			SetValue(s_configs[i][0], s_configs[i][1]);
		}
	}
}

}