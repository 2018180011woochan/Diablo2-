#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();

public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const DWORD& dwCount = 0)PURE;

	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"",
		const DWORD& dwCount = 0)PURE;

	virtual void Release()PURE;
};

#endif // !__TEXTURE_H__

