///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYScanner.h
/// @brief ������
///
/// @version 1.0
/// @author ������
/// @date 2014��11��22��
///
///////////////////////////////////////////////////////////////////////////////////////


#ifndef _ZYSCANNER_H_
#define _ZYSCANNER_H_

#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <vector>

using namespace std;

namespace DuiLib {

/// ������
class ZYScanner {
public:
	/// ����
	///
	/// @param dir ����Ŀ¼
	/// @param attribute �ļ�����
	/// @return �ڵ�ǰĿ¼����������ļ���
	virtual vector<CStdString> Scan(LPCTSTR dir, DWORD attribute);
};

}

#endif
