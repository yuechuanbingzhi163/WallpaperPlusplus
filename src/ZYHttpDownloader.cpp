///////////////////////////////////////////////////////////////////////////////////////
///
/// @file ZYHttpDownloader.cpp
/// @brief 下载器
///
/// @version 1.0
/// @author 曹中雨
/// @date 2014年11月22日
///
///////////////////////////////////////////////////////////////////////////////////////

#include "ZYHttpDownloader.h"
#include "ZYConfigurator.h"
#include "../include/curl/curl.h"
#include "../include/curl/easy.h"

namespace DuiLib {

ZYHttpDownloader::ZYHttpDownloader(ZYHttpDownloaderListener *cb) : m_cb(cb), m_run(TRUE) {
	m_mutex = ::CreateMutex(NULL, FALSE, _T("ZYHttpDownloader"));
	m_thread = ::CreateThread(NULL, 0, ZYHttpDownloader::DownloadThread, this, 0, NULL);
}

ZYHttpDownloader::~ZYHttpDownloader() {
	if (m_thread) {
		m_run = FALSE;
		::WaitForSingleObject(m_thread, INFINITE);
		::CloseHandle(m_thread);
	}
	::CloseHandle(m_mutex);
}

BOOL ZYHttpDownloader::Download(LPCTSTR url) {
	if (m_thread) {
		::WaitForSingleObject(m_mutex, INFINITE);
		m_urls.push_back(url);
		::ReleaseMutex(m_mutex);
		return TRUE;
	}
	return FALSE;
}

VOID ZYHttpDownloader::Reset() {
	::WaitForSingleObject(m_mutex, INFINITE);
	m_urls.clear();
	::ReleaseMutex(m_mutex);
}

LONG ZYHttpDownloader::GetUrlsSize() {
	LONG size;
	::WaitForSingleObject(m_mutex, INFINITE);
	size = m_urls.size();
	::ReleaseMutex(m_mutex);
	return size;
}

DWORD WINAPI ZYHttpDownloader::DownloadThread(LPVOID thiz) {
	ZYHttpDownloader *_thiz = (ZYHttpDownloader *) thiz;
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	while (_thiz->m_run) {
		::Sleep(10);
		CStdString url = _thiz->GetUrl();
		if (!url.IsEmpty()) {
			CHAR _url[PATH_MAX];
			LONG len;
			if ((len = ::WideCharToMultiByte(CP_OEMCP, 0, url.GetData(), url.GetLength(), _url, PATH_MAX, NULL, NULL))) {
				_url[len] = 0;
				curl_easy_setopt(curl, CURLOPT_URL, _url);
				CStdString dir = ZYConfigurator::GetInstance()->GetValue(_T("downloaddir"));
				LONG pos = dir.GetLength() - 1;
				if (dir.GetAt(pos) == _T('\\')) {
					dir = dir.Left(pos);
				}
				CStdString filename =_thiz->FixFilename(dir.GetData(), ZYHttpDownloader::GetFilename(url.GetData()));
				CStdString filepath;
				FILE *fp;
				filepath.Format(_T("%s\\%s"), dir.GetData(), filename.GetData());
				if ((fp = _tfopen(filepath.GetData(), _T("wb")))) {
					CURLcode res;
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
					res = curl_easy_perform(curl);
					fclose(fp);
					if (CURLE_OK == res) {
						if (_thiz->m_cb) {
							_thiz->m_cb->OnComplete(url.GetData(), filepath.GetData());
						}
						continue;
					}
					
				}
			}
			if (_thiz->m_cb) {
				_thiz->m_cb->OnError(url.GetData());
			}
		}
	}
	curl_easy_cleanup(curl);
	return 0;
}

CStdString ZYHttpDownloader::GetUrl() {
	CStdString url;
	::WaitForSingleObject(m_mutex, INFINITE);
	if (!m_urls.empty()) {
		url = *(m_urls.end() - 1);
		m_urls.pop_back();
	}
	::ReleaseMutex(m_mutex);
	return url;
}

CStdString ZYHttpDownloader::GetFilename(LPCTSTR url) {
	CStdString _url = url;
	CStdString filename = _url.Mid(_url.ReverseFind(_T('/')) + 1);
	if (filename.IsEmpty()) {
		filename = _T("download.tmp");
	}
	return filename;
}

CStdString ZYHttpDownloader::FixFilename(LPCTSTR dir, LPCTSTR filename) {
	CStdString _filename = filename;
	CStdString path;
	path.Format(_T("%s\\%s"), dir, filename);
	while (-1 !=_taccess(path.GetData(), 0)) {
		_filename.Format(_T("new_%s"), _filename.GetData());
		path.Format(_T("%s\\%s"), dir, _filename.GetData());
	}
	return _filename.GetData();
}

}
