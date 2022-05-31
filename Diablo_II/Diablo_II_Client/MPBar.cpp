#include "stdafx.h"
#include "MPBar.h"
#include "GameObject_Manager.h"
#include "Necromancer.h"

CMPBar::CMPBar()
	:m_iMP(0), m_UnitInfo(nullptr), m_pPlayer(nullptr)
{
}


CMPBar::~CMPBar()
{
	Release_GameObject();
}

HRESULT CMPBar::Ready_GameObject()
{
	return S_OK;
}

int CMPBar::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();

	int iHitDmg = int(m_UnitInfo->fMaxMP - m_UnitInfo->fMP);

	// 80은 mp볼의 세로 크기
	m_iMP = (80 * iHitDmg) / m_UnitInfo->fMaxMP;

	return OBJ_NOEVENT;
}

void CMPBar::Late_Update_GameObject()
{
}

void CMPBar::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"StatusBar", 1);
	float fCenterX = 0;
	float fCenterY = 0;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 0.f);
	D3DXMatrixTranslation(&matTrans, float(WINCX / 2) + 380.f, 595.f, 0.f);
	matWorld = matScale * matTrans;

	RECT rcMP;
	rcMP.left = fCenterX;
	rcMP.right = fCenterX + (pTexInfo->tImageInfo.Width);
	rcMP.bottom = fCenterY + (pTexInfo->tImageInfo.Height);
	rcMP.top = fCenterY + m_iMP;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rcMP, &_vec3(fCenterX, fCenterY - m_iMP, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMPBar::Release_GameObject()
{
}

CGameObject * CMPBar::Create()
{
	CGameObject* pInstance = new CMPBar;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
