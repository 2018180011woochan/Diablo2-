#pragma once

#ifndef __SINGLETEXTURE_H__
#define __SINGLETEXTURE_H__

#include "Texture.h"
class CSingle_Texture final :
	public CTexture
{
public:
	CSingle_Texture();
	virtual ~CSingle_Texture();

	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO m_tTexInfo;
};

#endif // !__SINGLETEXTURE_H__

