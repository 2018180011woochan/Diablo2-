#include "stdafx.h"
#include "Potal.h"
#include "GameObject_Manager.h"

CPotal::CPotal()
	: m_bisFont(false)
{
}


CPotal::~CPotal()
{
	Release_GameObject();
}

HRESULT CPotal::Ready_GameObject()
{
	return S_OK;
}

int CPotal::Update_GameObject()
{
	return OBJ_NOEVENT;
}

void CPotal::Late_Update_GameObject()
{
	UpdatePotal(0.5f);
}

void CPotal::Render_GameObject()
{
	TCHAR szPlayer_Strength[MAX_PATH] = L"";
	wchar_t wstring[] = L"카오스 생츄어리로 이동";

	swprintf_s(szPlayer_Strength, __T("%ls"), wstring);

	if (!m_tMonster.bisCreate)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Portal", L"CreatePortal", DWORD(m_tMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}
	if (m_tMonster.bisCreate)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Portal", L"ProgressPortal", DWORD(m_tMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

		if (m_bisFont)
		{
			RECT rPoint = { 0, 0, 300, 100 };
			CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Strength, lstrlen(szPlayer_Strength), &rPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CPotal::Release_GameObject()
{
}

void CPotal::UpdatePotal(float fSpeed)
{
	if (!m_tMonster.bisCreate)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > 13 && m_tMonster.tFrame.fStartFrame < 13.8)
		{
			m_tMonster.bisCreate = true;
		}
	}
	if (m_tMonster.bisCreate)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
			m_tMonster.tFrame.fStartFrame = 0.f;
	}
}

void CPotal::Initialize()
{
	m_tMonster.vPos = { 2350.f, 1650.f, 0.f };
	//m_tMonster.vPos = { 500, 500, 0.f };
	m_tMonster.tFrame = { 0.f, 15.f };
	m_tMonster.vSize = { 1.5f, 1.5f, 0.f };
	m_tMonster.bisPoison = false;
	m_tMonster.bisCreate = false;

	m_tFrame = m_tMonster.tFrame;

	m_tRect.top = m_tMonster.vPos.y - 20.f;
	m_tRect.left = m_tMonster.vPos.x - 20.f;
	m_tRect.bottom = m_tMonster.vPos.y + 20.f;
	m_tRect.right = m_tMonster.vPos.x + 20.f;
}

CGameObject * CPotal::Create()
{
	CGameObject* pInstance = new CPotal;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CPotal*>(pInstance)->Initialize();
	return pInstance;
}
