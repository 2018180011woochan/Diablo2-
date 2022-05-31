#include "stdafx.h"
#include "HPBar.h"
#include "GameObject_Manager.h"
#include "Necromancer.h"

CHPBar::CHPBar()
	:m_iHP(0), m_UnitInfo(nullptr), m_pPlayer(nullptr)
{
}


CHPBar::~CHPBar()
{
	Release_GameObject();
}

HRESULT CHPBar::Ready_GameObject()
{
	m_tInfo.vPos = { float(WINCX / 2) - 430.f, 650.f, 0.f };
	m_tInfo.vSize = { 100.f, 100.f, 0.f };

	return S_OK;
}

int CHPBar::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();
	
	int iHitDmg = int(m_UnitInfo->fMaxHP - m_UnitInfo->fHP);

	// 80은 hp볼의 세로 크기
	m_iHP = (80 * iHitDmg) / m_UnitInfo->fMaxHP;
	
	return 0;
}

void CHPBar::Late_Update_GameObject()
{
}

void CHPBar::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"StatusBar", 0);

	float fCenterX = 0;
	float fCenterY = 0;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 0.f);
	D3DXMatrixTranslation(&matTrans, float(WINCX / 2) - 480.f, 595.f , 0.f);
	matWorld = matScale * matTrans;

	RECT rcHP;
	rcHP.left = fCenterX;
	rcHP.right = fCenterX + (pTexInfo->tImageInfo.Width);
	rcHP.bottom = fCenterY + (pTexInfo->tImageInfo.Height);
	rcHP.top = fCenterY + m_iHP;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rcHP, &_vec3(fCenterX, fCenterY - m_iHP, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CHPBar::Release_GameObject()
{
}

CGameObject * CHPBar::Create()
{
	CGameObject* pInstance = new CHPBar;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
