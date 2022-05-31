#pragma once

#ifndef __GRAPHICDEVICE_H__
#define __GRAPHICDEVICE_H__

class CGraphic_Device final
{
public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphic_Device;
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
	static CGraphic_Device* m_pInstance;

private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device();
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice; }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
	LPD3DXFONT Get_Font() { return m_pFont; }
	LPD3DXLINE Get_Line() { return m_pLine; }
public:
	HRESULT Ready_Graphic_Device();
	void Release_Graphic_Device();
	void Render_Begin();
	void Render_End(HWND hWND = nullptr);
private:
	// �̽�Ű�� ��ġ�� �����ϰ� �������ִ� �İ�ü. 
	LPDIRECT3D9 m_pSDK;
	// �̰� ���������� ��ġ�� ������ ��. 
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
	LPD3DXLINE m_pLine;
};

#endif // !__GRAPHICDEVICE_H__
