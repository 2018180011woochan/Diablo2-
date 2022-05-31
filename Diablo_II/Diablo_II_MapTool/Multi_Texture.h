#pragma once

#ifndef __MULTITEXTURE_H__
#define __MULTITEXTURE_H__

#include "Texture.h"
class CMulti_Texture :
	public CTexture
{
public:
	explicit CMulti_Texture();
	virtual ~CMulti_Texture();

	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual void Release() override;

private:
	map<wstring, vector<TEXINFO*>> m_mapMultiTex;
};

#endif // !__MULTITEXTURE_H__

