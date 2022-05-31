#pragma once

#ifndef __FILEINFO_H__
#define __FILEINFO_H__

class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString ConvertReletivePath(CString strFullPath);
	static void DirInfoExtraction(const wstring& wstrFullPath, list<TEXPATH*>& rlistTexPath);
	static int FileCount(const wstring& wstrFullPath);
};

#endif // !__FILEINFO_H__

