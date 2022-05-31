#include "stdafx.h"
#include "StatWindow.h"
#include "GameObject_Manager.h"
#include "Necromancer.h"
#include "Key_Manager.h"

CStatWindow::CStatWindow()
	: m_pPlayer(nullptr)
{
}


CStatWindow::~CStatWindow()
{
	Release_GameObject();
}

HRESULT CStatWindow::Ready_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();
	return S_OK;
}

int CStatWindow::Update_GameObject()
{
	// 플레이어 정보 받아오기
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();

	Change_StatWnd(m_UnitInfo);

	if (bisOpenStatWnd == false)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CStatWindow::Late_Update_GameObject()
{
}

void CStatWindow::Render_GameObject()
{
	TCHAR szPlayer_Strength[MAX_PATH] = L"";
	int iPlayer_Strength = m_UnitInfo->fStrength;

	TCHAR szPlayer_Level[16] = L"";
	int iPlayer_Level = m_UnitInfo->iLevel;

	TCHAR szPlayer_EXP[16] = L"";
	int iPlayer_EXP = m_UnitInfo->iEXP;

	TCHAR szPlayer_NextLv[16] = L"";
	int iPlayer_NextLv = m_UnitInfo->iNextLevel;

	TCHAR szPlayer_Dex[16] = L"";
	int iPlayer_Dex = m_UnitInfo->fDexterity;

	TCHAR szPlayer_Vitality[16] = L"";
	int iPlayer_Vitality = m_UnitInfo->fVitality;

	TCHAR szPlayer_Energy[16] = L"";
	int iPlayer_Energy = m_UnitInfo->fEnergy;

	TCHAR szPlayer_Point[16] = L"";
	int iPlayer_Point = m_UnitInfo->fPoint;

	TCHAR szPlayer_Damage[16] = L"";
	int iPlayer_Damage = m_UnitInfo->fAttackDamage;

	TCHAR szPlayer_Defence[16] = L"";
	int iPlayer_Defence = m_UnitInfo->fDefence;

	TCHAR szPlayer_HP[16] = L"";
	int iPlayer_HP = m_UnitInfo->fHP;

	TCHAR szPlayer_MaxHP[16] = L"";
	int iPlayer_MaxHP = m_UnitInfo->fMaxHP;

	TCHAR szPlayer_MP[16] = L"";
	int iPlayer_MP = m_UnitInfo->fMP;

	TCHAR szPlayer_Max_MP[16] = L"";
	int iPlayer_MaxMP = m_UnitInfo->fMaxMP;
	
	swprintf_s(szPlayer_Strength, __T("%d"), iPlayer_Strength);
	swprintf_s(szPlayer_Level, __T("%d"), iPlayer_Level);
	swprintf_s(szPlayer_EXP, __T("%d"), iPlayer_EXP);
	swprintf_s(szPlayer_NextLv, __T("%d"), iPlayer_NextLv);
	swprintf_s(szPlayer_Dex, __T("%d"), iPlayer_Dex);
	swprintf_s(szPlayer_Vitality, __T("%d"), iPlayer_Vitality);
	swprintf_s(szPlayer_Energy, __T("%d"), iPlayer_Energy);
	swprintf_s(szPlayer_Point, __T("%d"), iPlayer_Point);
	swprintf_s(szPlayer_Damage, __T("%d"), iPlayer_Damage);
	swprintf_s(szPlayer_Defence, __T("%d"), iPlayer_Defence);
	swprintf_s(szPlayer_HP, __T("%d"), iPlayer_HP);
	swprintf_s(szPlayer_MaxHP, __T("%d"), iPlayer_MaxHP);
	swprintf_s(szPlayer_MP, __T("%d"), iPlayer_MP);
	swprintf_s(szPlayer_Max_MP, __T("%d"), iPlayer_MaxMP);

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Window", 5);
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX - fCenterX - 700, WINCY - fCenterY - 150, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 힘
	RECT rStrength = { -97, -168, 17, -118 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Strength, lstrlen(szPlayer_Strength), &rStrength, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 렙
	RECT rLevel = { -169, -216, -79, -176 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Level, lstrlen(szPlayer_Level), &rLevel, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 경치
	RECT rExp = { -106, -216, 6, -166 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_EXP, lstrlen(szPlayer_EXP), &rExp, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 다음레벨
	RECT rNextLV = { 84, -214, 184, -164 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_NextLv, lstrlen(szPlayer_NextLv), &rNextLV, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 덱스
	RECT rDex = { -97, -92, 17, -42 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Dex, lstrlen(szPlayer_Dex), &rDex, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 바이탈
	RECT rVital = { -97, 18, 17, 68 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Vitality, lstrlen(szPlayer_Vitality), &rVital, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 에너지
	RECT rEnergy = { -97, 96, 17, 136 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Energy, lstrlen(szPlayer_Energy), &rEnergy, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 포인트
	RECT rPoint = { -65, 165, 15, 215 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Point, lstrlen(szPlayer_Point), &rPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Damage
	RECT rDamage = { 145, -171, 235, -121 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Damage, lstrlen(szPlayer_Damage), &rDamage, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Defence
	RECT rDefence = { 155, -141, 235, -91 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Defence, lstrlen(szPlayer_Defence), &rDefence, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// HP
	RECT rHP = { 89, 50, 189, 100 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_HP, lstrlen(szPlayer_HP), &rHP, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// maxHP
	RECT rMaxHP = { 144, 50, 244, 100 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_MaxHP, lstrlen(szPlayer_MaxHP), &rMaxHP, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// MP
	RECT rMP = { 89, 96, 189, 146 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_MP, lstrlen(szPlayer_MP), &rMP, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	// maxMP
	RECT rMaxMP = { 144, 96, 244, 146 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Max_MP, lstrlen(szPlayer_Max_MP), &rMaxMP, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CStatWindow::Release_GameObject()
{
}

CGameObject * CStatWindow::Create()
{
	CGameObject* pInstance = new CStatWindow;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CStatWindow::Change_StatWnd(UNITINFO* _tUnitInfo)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_LBUTTON))
	{
		if (bisOpenStatWnd)
		{
			// out
			if (pt.x > 340 && pt.x < 378 &&
				pt.y > 515 && pt.y < 553)
			{
				bisOpenStatWnd = false;
			}
			// strenght
			if (pt.x > 274 && pt.x < 321 &&
				pt.y > 123 && pt.y < 145)
			{
				if (m_UnitInfo->fPoint <= 0)
					return;
				m_UnitInfo->fPoint--;
				m_UnitInfo->fStrength++;
				m_UnitInfo->fAttackDamage += 300 * m_UnitInfo->iLevel;
			}
			// dex
			if (pt.x > 274 && pt.x < 321 &&
				pt.y > 203 && pt.y < 225)
			{
				if (m_UnitInfo->fPoint <= 0)
					return;
				m_UnitInfo->fPoint--;
				m_UnitInfo->fDexterity++;
				m_UnitInfo->fDefence += 2;
			}
			// vital
			if (pt.x > 274 && pt.x < 321 &&
				pt.y > 311 && pt.y < 333)
			{
				if (m_UnitInfo->fPoint <= 0)
					return;
				m_UnitInfo->fPoint--;
				m_UnitInfo->fVitality++;
				m_UnitInfo->fAttackDamage += 100 * m_UnitInfo->iLevel;
				m_UnitInfo->fMaxHP += 500 * m_UnitInfo->iLevel;
				m_UnitInfo->fHP += 500 * m_UnitInfo->iLevel;
			}
			// energy
			if (pt.x > 274 && pt.x < 321 &&
				pt.y > 391 && pt.y < 411)
			{
				if (m_UnitInfo->fPoint <= 0)
					return;
				m_UnitInfo->fPoint--;
				m_UnitInfo->fEnergy++;
				m_UnitInfo->fDefence++;
				m_UnitInfo->fMaxMP += 300 * m_UnitInfo->iLevel;
				m_UnitInfo->fMP += 300 * m_UnitInfo->iLevel;
			}
		}
	}
}
