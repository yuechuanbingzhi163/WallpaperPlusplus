///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYImageSniffer.h
/// @brief 嗅探器
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ZYIMAGESNIFFER_H_
#define _ZYIMAGESNIFFER_H_

#include "ZYHttpDownloader.h"
#include "../include/DuiLib/UIlib.h"
#include <Windows.h>

namespace DuiLib {

/// 嗅探器回调
class ZYImageSnifferListener {
public:
	/// 进度改变事件
	///
	/// @param progress 当前进度
	virtual VOID OnProgress(LONG progress) = 0;
};

/// 嗅探器
class ZYImageSniffer : public ZYHttpDownloaderListener {
public:
	/// 构造函数
	///
	/// @param cb 嗅探器回调
	ZYImageSniffer(ZYImageSnifferListener *cb);

	/// 析构函数
	~ZYImageSniffer();

	/// 获取制定页面中的图片
	///
	/// @param url 页面地址
	/// @return 返回 TRUE 开始获取, 返回 FALSE 当前仍有任务进行
	virtual BOOL Sniff(LPCTSTR url);
	
	/// 下载完成事件
	///
	/// @param url 下载地址
	/// @param fileparh 文件位置
	virtual VOID OnComplete(LPCTSTR url, LPCTSTR filepath);

	/// 下载失败事件
	/// @param url 下载地址
	virtual VOID OnError(LPCTSTR url);

	/// 检查文件后缀
	///
	/// 通过同配置项中的后缀比较检查是否为图片格式
	/// @param filename 文件名
	/// @return 返回 TRUE 是图片, 返回 FALSE不是图片
	static BOOL CheckFileextension(LPCTSTR filename);

	/// 检查图像大小
	///
	/// 通过同配置项中的最小图片大小判断是否符合壁纸大小
	/// @param filepath 文件位置
	/// @return 返回 TRUE 符合大小, 返回 FALSE不符
	static BOOL CheckImageSize(LPCTSTR filepath);

protected:
	/// 从文件中获取图片 url
	///
	/// @param filepath 文件路径
	/// @return 图片地址
	virtual vector<CStdString> GetImageUrls(LPCTSTR filepath);

	/// 当前状态
	DWORD m_state;

	/// 图片总数
	LONG m_size;

	/// 嗅探器回调
	ZYImageSnifferListener *m_cb;

	/// 下载器
	ZYHttpDownloader *m_httpDownloader;
};

}

#endif
