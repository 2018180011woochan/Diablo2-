#include "stdafx.h"
#include "MyStatusBar.h"
#include "GameObject_Manager.h"
#include "Necromancer.h"

CMyStatusBar::CMyStatusBar()
	: m_iExpBar(0), m_iStamina(0), m_bStatLightUp(false)
{
}


CMyStatusBar::~CMyStatusBar()
{
	Release_GameObject();
}

HRESULT CMyStatusBar::Ready_GameObject()
{
	return S_OK;
}

int CMyStatusBar::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();


	int iRunPoint = int(m_UnitInfo->iMaxStamina - m_UnitInfo->iStamina);

	// 103은 스태미나의 가로 크기
	m_iStamina = (103 * iRunPoint) / m_UnitInfo->iMaxStamina;



	int iEXPPoint = int(m_UnitInfo->iNextLevel - m_UnitInfo->iEXP);

	// 80은 경험치의 가로 크기
	m_iExpBar = (103 * iEXPPoint) / m_UnitInfo->iNextLevel;
	return 0;
}

void CMyStatusBar::Late_Update_GameObject()
{
}

void CMyStatusBar::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"StatusBar", 2);
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;

	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 0.f);
	D3DXMatrixTranslation(&matTrans, float(WINCX / 2), 650.f, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	/// 스태미나
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"StatusBar", 6);
	fCenterX = 0;
	fCenterY = 0;

	D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 0.f);
	D3DXMatrixTranslation(&matTrans, float(WINCX / 2) - 30, 682.f, 0.f);
	matWorld = matScale * matTrans;

	RECT rcStamina;

	rcStamina.left = fCenterX + (pTexInfo->tImageInfo.Width) - m_iStamina;
	rcStamina.right = fCenterX;
	rcStamina.bottom = fCenterY;
	rcStamina.top = fCenterY - (pTexInfo->tImageInfo.Height);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rcStamina, &_vec3(fCenterX + m_iStamina  , fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	/// 경험치 바
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"StatusBar", 6);
	fCenterX = 0;
	fCenterY = 0;

	D3DXMatrixScaling(&matScale, 1.5f, 0.2f, 0.f);
	D3DXMatrixTranslation(&matTrans, float(WINCX / 2) - 30, 663.f, 0.f);
	matWorld = matScale * matTrans;

	RECT rcEXP;

	rcEXP.left = fCenterX + (pTexInfo->tImageInfo.Width) - m_iExpBar;
	rcEXP.right = fCenterX;
	rcEXP.bottom = fCenterY;
	rcEXP.top = fCenterY - (pTexInfo->tImageInfo.Height);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rcEXP, &_vec3(fCenterX + m_iExpBar, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 0, 0));

	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();
	///// 렙업하면 스탯창 활성화
	if (m_UnitInfo->fPoint > 0.f)
	{
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"StatusBar", 3);
		fCenterX = pTexInfo->tImageInfo.Width >> 1;
		fCenterY = pTexInfo->tImageInfo.Height >> 1;

		D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 0.f);
		D3DXMatrixTranslation(&matTrans, float(WINCX / 2) - 235, 690.f, 0.f);
		matWorld = matScale * matTrans;


		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMyStatusBar::Release_GameObject()
{
	for (auto& pStatusBar : m_vecUI)
		Safe_Delete(pStatusBar);
	m_vecUI.clear();
	m_vecUI.shrink_to_fit();
}

CGameObject * CMyStatusBar::Create()
{
	CGameObject* pInstance = new CMyStatusBar;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
