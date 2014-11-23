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

#include "ZYImageSniffer.h"
#include "ZYConfigurator.h"
#include "ZYScanner.h"

#include "stb_image.c"

namespace DuiLib {

ZYImageSniffer::ZYImageSniffer(ZYImageSnifferListener *cb) : m_state(0), m_cb(cb) {
	m_httpDownloader = new ZYHttpDownloader(this);
}

ZYImageSniffer::~ZYImageSniffer() {
	delete m_httpDownloader;
}

BOOL ZYImageSniffer::Sniff(LPCTSTR url) {
	if (!m_state) {
		m_httpDownloader->Download(url);
		m_state = 1;
		return TRUE;
	}
	return FALSE;
}

VOID ZYImageSniffer::OnComplete(LPCTSTR url, LPCTSTR filepath) {
	if (1 == m_state) {
		vector<CStdString> urls = GetImageUrls(filepath);
		::DeleteFile(filepath);
		m_size = urls.size();
		if (m_size) {
			if (m_cb) {
				m_cb->OnProgress(50);
			}
			for (vector<CStdString>::iterator it = urls.begin(); it != urls.end(); it++) {
				m_httpDownloader->Download(*it);
			}
			m_state = 2;
		} else {
			if (m_cb) {
				m_cb->OnProgress(100);
			}
			m_state = 0;
		}
	} else if (2 == m_state) {
		LONG size = m_httpDownloader->GetUrlsSize();
		if (m_cb) {
			m_cb->OnProgress((m_size - size) * 100 / m_size);
		}
		if (!ZYImageSniffer::CheckFileextension(filepath) || !ZYImageSniffer::CheckImageSize(filepath)) {
			::DeleteFile(filepath);
		}
		if (!size) {
			m_state = 0;
		}
	}
}

VOID ZYImageSniffer::OnError(LPCTSTR url) {
	if (1 == m_state) {
		m_state = 0;
		if (m_cb) {
			m_cb->OnProgress(100);
		}
	} else if (2 == m_state) {
		LONG size = m_httpDownloader->GetUrlsSize();
		if (m_cb) {
			m_cb->OnProgress((m_size - size) * 100 / m_size);
		}
		if (!size) {
			m_state = 0;
		}
	}
}

BOOL ZYImageSniffer::CheckFileextension(LPCTSTR filename) {
	CStdString _filename = filename;
	if (_filename.GetAt(_filename.GetLength() - 1) != _T('.') && -1 != ZYConfigurator::GetInstance()->GetValue(_T("fileext")).Find(_filename.Mid(_filename.ReverseFind(_T('.'))))) {
		return TRUE;
	}
	return FALSE;
}

BOOL ZYImageSniffer::CheckImageSize(LPCTSTR filepath) {
	HANDLE file;
	if (INVALID_HANDLE_VALUE != (file = ::CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL))) {
		DWORD size;
		if (size  = ::GetFileSize(file, NULL)) {
			DWORD read = 0;
			LPBYTE data = new BYTE[size];
			::ReadFile(file, data, size, &read, NULL);
			::CloseHandle(file);
			if (read == size) {
				INT x = 0, y = 0, n = 0;
				if (::stbi_load_from_memory(data, size, &x, &y, &n, 4)) {
					ZYConfigurator *configurator = ZYConfigurator::GetInstance();
					if (_ttoi(configurator->GetValue(_T("cx")).GetData()) <= x && _ttoi(configurator->GetValue(_T("cy")).GetData()) <= y) {
						delete data;
						return TRUE;
					}
				}
				
			}
			delete data;
		}
	}
	return FALSE;
}

vector<CStdString> ZYImageSniffer::GetImageUrls(LPCTSTR filepath) {
	vector<CStdString> urls;
	LPCSTR urlchar = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./=?&_-%";
	LPCSTR http = "http://";
	CHAR buf[2] = {0};
	FILE *fp;
	if ((fp = _tfopen(filepath, _T("rb")))) {
		CHAR url[PATH_MAX];
		UINT pos = 0;
		while (0 < fread(buf, 1, 1, fp)) {
			url[pos] = buf[0];
			if (pos < strlen(http)) {
				if (buf[0] != http[pos]) {
					pos = 0;
				} else {
					pos++;
				}
			} else  {
				if (strstr(urlchar, buf)) {
					pos++;
				} else {
					TCHAR _url[PATH_MAX];
					LONG len;
					if (len = ::MultiByteToWideChar(CP_OEMCP, 0, url, pos, _url, PATH_MAX)) {
						_url[len] = _T('\0');
						if (ZYImageSniffer::CheckFileextension(ZYHttpDownloader::GetFilename(_url))) {
							urls.push_back(_url);
						}
					}
					pos = 0;
				}
				
			}
		}
		fclose(fp);
	}
	return urls;
}

}
