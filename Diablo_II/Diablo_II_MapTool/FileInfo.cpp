#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertReletivePath(CString strFullPath)
{
	TCHAR szReletivePath[MAX_PATH] = L"";

	TCHAR szCurrentDirectory[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	PathRelativePathTo(szReletivePath, szCurrentDirectory, FILE_ATTRIBUTE_DIRECTORY, strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);
	return CString(szReletivePath);
}

void CFileInfo::DirInfoExtraction(const wstring & wstrFullPath, list<TEXPATH*>& rlistTexPath)
{
	CFileFind Find;

	wstring wstrPath = wstrFullPath + L"\\*.*";
	Find.FindFile(wstrPath.c_str());
	BOOL bContinue = TRUE;
	while (bContinue)
	{
		bContinue = Find.FindNextFile();
		if (Find.IsDots())
			continue;
		else if (Find.IsDirectory())
		{
			DirInfoExtraction(Find.GetFilePath().GetString(), rlistTexPath);
		}
		else
		{
			if (Find.IsSystem())
				continue;
			TEXPATH* pTexInfo = new TEXPATH;
			TCHAR szPathBuf[MAX_PATH] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());
			PathRemoveFileSpec(szPathBuf);

			TCHAR szObject_State_Key[MAX_PATH] = L"";
			lstrcpy(szObject_State_Key, szPathBuf);
			pTexInfo->dwCount = FileCount(szPathBuf);

			wstring wstrFileName = Find.GetFileTitle().GetString();
			wstrFileName = wstrFileName.substr(0, wstrFileName.length() - 1) + L"%d.png";

			PathCombine(szPathBuf, szPathBuf, wstrFileName.c_str());
			pTexInfo->wstrRelativePath = CFileInfo::ConvertReletivePath(szPathBuf);
			pTexInfo->wstrStateKey = PathFindFileName(szObject_State_Key);

			PathRemoveFileSpec(szObject_State_Key);
			pTexInfo->wstrObjectKey = PathFindFileName(szObject_State_Key);
			rlistTexPath.emplace_back(pTexInfo);
			bContinue = FALSE;
		}
	}
}

int CFileInfo::FileCount(const wstring & wstrFullPath)
{
	CFileFind Find;
	wstring wstrPath = wstrFullPath + L"\\*.*";
	BOOL bContinue = Find.FindFile(wstrPath.c_str());
	int iCount = 0;
	while (bContinue)
	{
		bContinue = Find.FindNextFile();
		if (Find.IsDots() || Find.IsSystem())
			continue;
		++iCount;
	}

	return iCount;
}
