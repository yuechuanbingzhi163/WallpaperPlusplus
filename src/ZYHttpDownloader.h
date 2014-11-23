///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYHttpDownloader.h
/// @brief 下载器
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYHTTPDOWNLOADER_H_
#define _ZYHTTPDOWNLOADER_H_

#include "ZYScanner.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>
#include <vector>

using namespace std;

namespace DuiLib {

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

/// 下载回调
class ZYHttpDownloaderListener {
public:
	/// 下载完成事件
	///
	/// @param url 下载地址
	/// @param fileparh 文件位置
	virtual VOID OnComplete(LPCTSTR url, LPCTSTR filepath) = 0;

	/// 下载失败事件
	///
	/// @param url 下载地址
	virtual VOID OnError(LPCTSTR url) = 0;
};

/// 下载器
class ZYHttpDownloader {
public:
	/// 构造函数
	///
	/// @param cb 下载回调
	ZYHttpDownloader(ZYHttpDownloaderListener *cb);

	/// 析构函数
	virtual ~ZYHttpDownloader();

	/// 添加下载任务
	///
	/// @param url 下载地址
	/// @return 返回 TRUE 添加成功, 返回 FALSE 添加失败
	virtual BOOL Download(LPCTSTR url);

	/// 清空下载队列
	virtual VOID Reset();

	/// 获取下载任务数量
	///
	/// @return 数量
	virtual LONG GetUrlsSize();

	/// 获取文件名
	///
	/// @param url 下载地址
	/// @return 文件名
	static CStdString GetFilename(LPCTSTR url);
	
	/// 下载线程
	///
	/// @param thiz 初始化参数
	/// @return 线程结果
	static DWORD WINAPI DownloadThread(LPVOID thiz);

protected:
	/// 从下载队列中获取一个下载地址
	///
	/// @return 下载地址
	virtual CStdString GetUrl();

	/// 修正文件名
	///
	/// @param dir 目录
	/// @param filename 文件名
	/// @return 修正的文件名
	virtual CStdString FixFilename(LPCTSTR dir, LPCTSTR filename);

	/// 下载回调
	ZYHttpDownloaderListener *m_cb;

	/// 下载队列
	vector<CStdString> m_urls;

	/// 线程控制标识
	BOOL m_run;

	/// 线程句柄
	HANDLE m_thread;

	/// 内存访问互斥体
	HANDLE m_mutex;
};

}

#endif
