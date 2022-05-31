#include "stdafx.h"
#include "CorpseExplodeGuts.h"
#include "GameObject_Manager.h"

CCorpseExplodeGuts::CCorpseExplodeGuts()
{
}


CCorpseExplodeGuts::~CCorpseExplodeGuts()
{
	Release_GameObject();
}

HRESULT CCorpseExplodeGuts::Ready_GameObject()
{
	return S_OK;
}

int CCorpseExplodeGuts::Update_GameObject()
{
	if (m_tBullet.bIsDead)
		return OBJ_DEAD;
	
	return OBJ_NOEVENT;
}

void CCorpseExplodeGuts::Late_Update_GameObject()
{
	if (!m_tBullet.bIsDead)
		CorpseExplodeGuts_FrameMove(1.f);
	
}

void CCorpseExplodeGuts::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"CorpseExplodeGuts", DWORD(m_tBullet.tFrame.fStartFrame));
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
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
	
	if (m_tBullet.bIsDead)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"CorpseExplodeGuts", 25);
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
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
}

void CCorpseExplodeGuts::Release_GameObject()
{
}

CGameObject * CCorpseExplodeGuts::Create(BULLET & _tBullet)
{
	CGameObject* pInstance = new CCorpseExplodeGuts;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CCorpseExplodeGuts*>(pInstance)->Initialize(_tBullet);
	return pInstance;
}

void CCorpseExplodeGuts::Initialize(BULLET & _tBullet)
{
	m_tBullet = _tBullet;
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	m_tBullet.vPos = { (float)pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (float)pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f };

	m_tBullet.tFrame = { 0.f, 26.f };
	m_tBullet.fSpeed = 300.f;
	m_tBullet.vSize = { 1.5f, 1.5f, 0.f };

	m_tRect.top = m_tBullet.vPos.y - 100.f;
	m_tRect.left = m_tBullet.vPos.x - 100.f;
	m_tRect.bottom = m_tBullet.vPos.y + 100.f;
	m_tRect.right = m_tBullet.vPos.x + 100.f;

	m_tBullet.fAttack = 1000.f;
	m_tBullet.bIsDead = false;
}

void CCorpseExplodeGuts::CorpseExplodeGuts_FrameMove(float fSpeed)
{
	m_tBullet.tFrame.fStartFrame += m_tBullet.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tBullet.tFrame.fStartFrame > m_tBullet.tFrame.fEndFrame)
	{
		m_tBullet.tFrame.fStartFrame = 25.f;
		m_tBullet.bIsDead = true;
		m_tBullet.fAttack = 0.f;
	}
}

