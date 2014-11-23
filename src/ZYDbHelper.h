///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYDbHelper.cpp
/// @brief ���ݿ⹤��
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
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

/// ���ݿ�����ӿ�
class ZYDbHelper {
public:
	/// ��������
	virtual ~ZYDbHelper();

	/// SQL ��ѯ
	///
	/// @param sql SQL ��ѯ���
	/// @param qset ��ѯ����
	/// @return ���� TRUE ��ѯ�ɹ�, ���� FALSE ��ѯʧ��
	virtual BOOL Query(LPCTSTR sql, vector<vector<CStdString>> *qset);

	/// ��ȡ���ݿ�����ӿ�Ψһʵ��
	///
	/// @return ���ݿ�����ӿ�ʵ��
	static ZYDbHelper *GetInstance();

protected:
	/// ˽�й��캯��
	ZYDbHelper();

	/// ���ݿ��ѯ����ص�
	static INT GetData(LPVOID qset, INT count, LPSTR *column, LPSTR *name);

	/// ���ݿ���
	sqlite3 *m_db;
};

}

#endif
