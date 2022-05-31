#pragma once

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

class CTexture;
class CTexture_Manager
{
public:
	enum TEX_ID { SINGLE_TEX, MULTI_TEX };
public:
	static CTexture_Manager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTexture_Manager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CTexture_Manager();
	~CTexture_Manager();
public:
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0);
	HRESULT Insert_Texture(const TEX_ID eTexID, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0);
	void Release();

private:
	static CTexture_Manager* m_pInstance;
	map<wstring, CTexture*> m_mapTexture;
};

#endif // !__TEXTUREMANAGER_H__

