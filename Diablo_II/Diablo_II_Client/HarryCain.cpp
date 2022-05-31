#include "stdafx.h"
#include "HarryCain.h"
#include "GameObject_Manager.h"

CHarryCain::CHarryCain()
	: m_bIsQuestAccess(true)
{
}


CHarryCain::~CHarryCain()
{
	Release_GameObject();
}

HRESULT CHarryCain::Ready_GameObject()
{
	return S_OK;
}

int CHarryCain::Update_GameObject()
{
	Update_Monster_Rect();
	return OBJ_NOEVENT;
}

void CHarryCain::Late_Update_GameObject()
{
	Monster_FrameMove(1.f);
}

void CHarryCain::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Cain", L"00", DWORD(m_tFrame.fStartFrame));
	if (nullptr == pTexInfo)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
	matWorld = matScale * matTrans;

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
	//CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	//CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

	if (m_bIsQuestAccess)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Cain", L"01", 0);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) + 40.f, m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - 60.f, 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CHarryCain::Release_GameObject()
{
}

void CHarryCain::Monster_FrameMove(float fSpeed)
{
	m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
		m_tMonster.tFrame.fStartFrame = 0.f;
}

void CHarryCain::Initialize()
{
	m_tMonster.vPos = { 2050.f, 1350.f, 0.f };
	m_tMonster.tFrame = { 0.f, 5.f };
	m_tMonster.vSize = { 1.5f, 1.5f, 0.f };
	m_tMonster.bisPoison = false;

	m_tFrame = m_tMonster.tFrame;

	m_tRect.top = m_tMonster.vPos.y - 20.f;
	m_tRect.left = m_tMonster.vPos.x - 20.f;
	m_tRect.bottom = m_tMonster.vPos.y + 20.f;
	m_tRect.right = m_tMonster.vPos.x + 20.f;
}

CGameObject * CHarryCain::Create()
{
	CGameObject* pInstance = new CHarryCain;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CHarryCain*>(pInstance)->Initialize();
	return pInstance;
}
