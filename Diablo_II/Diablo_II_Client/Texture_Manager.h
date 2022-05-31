#pragma once

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

class CTexture;
class CTexture_Manager
{
public:
	enum TEX_ID { SINGLE_TEX, MULTI_TEX };
public:
	DECLARE_SINGLETON(CTexture_Manager)
private:
	CTexture_Manager();
	~CTexture_Manager();
public:
	HRESULT LoadImagePath(const wstring& wstrFilePath);
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0);
	HRESULT Insert_Texture(const TEX_ID eTexID, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0);
	void Release();

private:
	map<wstring, CTexture*> m_mapTexture;
};

#endif // !__TEXTUREMANAGER_H__

