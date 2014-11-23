///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYConfigurator.cpp
/// @brief ������
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYCONFIGURATOR_H_
#define _ZYCONFIGURATOR_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <map>

using namespace std;

namespace DuiLib {

/// ������
class ZYConfigurator {
public:
	/// ��������
	virtual ~ZYConfigurator();

	/// ��ȡ����
	///
	/// @param key ��������
	/// @return ����
	virtual CStdString GetValue(LPCTSTR key);

	/// ��������
	///
	/// @param key ��������
	/// @param value ����
	virtual VOID SetValue(LPCTSTR key, LPCTSTR value);

	/// ��ȡ������Ψһʵ��
	///
	/// @return ������ʵ��
	static ZYConfigurator *GetInstance();

protected:
	/// ˽�й��캯��
	ZYConfigurator();

	/// ���������
	map<CStdString, CStdString> m_configs;
};

}

#endif
