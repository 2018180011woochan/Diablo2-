#include "stdafx.h"
#include "PoisonExplosion.h"


CPoisonExplosion::CPoisonExplosion()
{
}


CPoisonExplosion::~CPoisonExplosion()
{
	Release_GameObject();
}

HRESULT CPoisonExplosion::Ready_GameObject()
{
	return S_OK;
}

int CPoisonExplosion::Update_GameObject()
{
	if (m_tBullet.bIsDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CPoisonExplosion::Late_Update_GameObject()
{
	PoisonExplosion_FrameMove(1.f);
}

void CPoisonExplosion::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"poisonGas", DWORD(m_tBullet.tFrame.fStartFrame));
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

	HDC hDC = GetDC(g_hWND);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPoisonExplosion::Release_GameObject()
{
}

CGameObject * CPoisonExplosion::Create(BULLET & _tBullet)
{
	CGameObject* pInstance = new CPoisonExplosion;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CPoisonExplosion*>(pInstance)->Initialize(_tBullet);
	return pInstance;
}

void CPoisonExplosion::Initialize(BULLET & _tBullet)
{
	m_tBullet = _tBullet;
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	m_tBullet.vPos = { (float)pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (float)pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f };

	m_tBullet.tFrame = { 0.f, 36.f };
	m_tBullet.fSpeed = 300.f;
	m_tBullet.vSize = { 3.f, 3.f, 0.f };

	m_tRect.top = m_tBullet.vPos.y - 100.f;
	m_tRect.left = m_tBullet.vPos.x - 100.f;
	m_tRect.bottom = m_tBullet.vPos.y + 100.f;
	m_tRect.right = m_tBullet.vPos.x + 100.f;

	m_tBullet.fAttack = 1.f;
	m_tBullet.bIsDead = false;
}

void CPoisonExplosion::PoisonExplosion_FrameMove(float fSpeed)
{
	m_tBullet.tFrame.fStartFrame += m_tBullet.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tBullet.tFrame.fStartFrame > m_tBullet.tFrame.fEndFrame)
	{
		m_tBullet.tFrame.fStartFrame = 35.f;
		m_tBullet.bIsDead = true;
		m_tBullet.fAttack = 0.f;
	}
}
