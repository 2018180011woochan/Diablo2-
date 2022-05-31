#include "stdafx.h"
#include "Stage.h"
#include "GameObject_Manager.h"
#include "Key_Manager.h"
#include "Tile.h"
#include "MapObj.h"
#include "Necromancer.h"
// UI //
#include "MyStatusBar.h"
#include "HPBar.h"
#include "MPBar.h"
// WINDOW //
#include "SkillWindow.h"
#include "StatWindow.h"
#include "QuestWindow.h"
// MONSTER //
#include "Wraith.h"
#include "SK2.h"
#include "SK.h"
#include "Diablo.h"
#include "Demon.h"


CStage::CStage()
	: m_pGameObject_Manager(CGameObject_Manager::Get_Instance()),
	pSkillWnd(nullptr), pStatWnd(nullptr), pQuestWnd(nullptr) , m_bSkillSet(false), pPlayer(nullptr), m_dwSkillSet(9), pDiablo(nullptr), m_dwSummonSkillSet(0), m_bisSkillType(false)
{
}


CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	CGameObject* pTile = CTile::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_TERRAIN, pTile);

	CGameObject* pMapObj = CMapObj::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_MAPOBJECT, pMapObj);

	CGameObject* pMyStatusBar = CMyStatusBar::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pMyStatusBar);

	pMyStatusBar = CHPBar::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pMyStatusBar);

	pMyStatusBar = CMPBar::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pMyStatusBar);

	pPlayer = CNecromancer::Create({ float(WINCX >> 1), float(WINCY >> 1) * 5.f, 0.f });
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_PLAYER, pPlayer);

	// 레이스 생성
	if (FAILED(m_pGameObject_Manager->LoadMonster(TEXT("../Data/WraithSave.dat"))))
	{
		return E_FAIL;
	}

	// SK2 생성
	if (FAILED(m_pGameObject_Manager->LoadMonster(TEXT("../Data/SK2Save.dat"))))
	{
		return E_FAIL;
	}

	// SK 생성
	if (FAILED(m_pGameObject_Manager->LoadMonster(TEXT("../Data/SKSave.dat"))))
	{
		return E_FAIL;
	}

	// Demon 생성
	if (FAILED(m_pGameObject_Manager->LoadMonster(TEXT("../Data/DemonSave.dat"))))
	{
		return E_FAIL;
	}

	// Diablo 생성
	if (FAILED(m_pGameObject_Manager->LoadMonster(TEXT("../Data/DiabloSave.dat"))))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CStage::Update_Scene()
{
	pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(pPlayer)->Get_Necromancer();

	pDiablo = CGameObject_Manager::Get_Instance()->Get_Diablo();



	m_pGameObject_Manager->Update_GameObject_Manager();
	SkillSet();
	return 0;
}

void CStage::Late_Update_Scene()
{
	m_pGameObject_Manager->Late_Update_GameObject_Manager();

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_K))
	{
		bisOpenSkillWnd = true;
		pSkillWnd = CSkillWindow::Create();
		m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pSkillWnd);
	}

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_S))
	{
		bisOpenStatWnd = true;
		pStatWnd = CStatWindow::Create();
		m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pStatWnd);
	}

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_Q))
	{
		bisOpenQuestWnd = true;
		pStatWnd = CQuestWindow::Create();
		m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pStatWnd);
	}

}

void CStage::Render_Scene()
{
	m_pGameObject_Manager->Render_GameObject_Manager();

	TCHAR szSkeletonCnt[16] = L"";
	int iSkeletonCnt = dynamic_cast<CNecromancer*>(pPlayer)->Get_SkeletonCount();
	swprintf_s(szSkeletonCnt, __T("%d"), iSkeletonCnt);

	// 스켈레톤 소환시 UI
	if (dynamic_cast<CNecromancer*>(pPlayer)->Get_SkeletonCount() != 0)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Assistor", 1);
		if (pTexInfo == nullptr)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, fCenterX, fCenterY, 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		RECT rSkeletonCnt = { 0, 0, 50, 30 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szSkeletonCnt, lstrlen(szSkeletonCnt), &rSkeletonCnt, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	// 블골 소환시 UI
	if (dynamic_cast<CNecromancer*>(pPlayer)->Get_isBloodGolemAlive())
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Assistor", 0);
		if (pTexInfo == nullptr)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, fCenterX * 2, fCenterY, 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	// 현재 장착 스킬
	if (m_bisSkillType)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", m_dwSkillSet);
		if (pTexInfo == nullptr)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, 975, 687, 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (!m_bisSkillType)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", m_dwSummonSkillSet);
		if (pTexInfo == nullptr)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;

		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, 975, 687, 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	///////////////////////////////////////////////////// 스킬 셋 /////////////////////////////////////////////////////////////////////
	if (m_bSkillSet)
	{
		// 티스
		if (m_UnitInfo->tSkillCheck.Teeth)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 0);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 본아머
		if (m_UnitInfo->tSkillCheck.BoneArmor)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 1);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 포이즌대거
		if (m_UnitInfo->tSkillCheck.PoisonDagger)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 2);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 2, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 시폭
		if (m_UnitInfo->tSkillCheck.CorpseExplosion)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 3);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 3, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 본월
		if (m_UnitInfo->tSkillCheck.BornWall)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 4);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 4, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 포이즌 익스프레젼
		if (m_UnitInfo->tSkillCheck.PoisonExplosion)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 5);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 5, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 본스피어
		if (m_UnitInfo->tSkillCheck.BoneSpear)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 6);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 6, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 본프리즌
		if (m_UnitInfo->tSkillCheck.BonePrison)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 7);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 7, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 포이즌노바
		if (m_UnitInfo->tSkillCheck.PoisonNova)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 8);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 8, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 본스피릿
		if (m_UnitInfo->tSkillCheck.BornSpirit)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"BornSkill", 9);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 9, 625, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		/// 소환 스킬

		// 스켈레톤 마스터리
		if (m_UnitInfo->tSummonSkillCheck.SkeletonMastery)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 0);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		// 레이즈 스켈레톤
		if (m_UnitInfo->tSummonSkillCheck.RaiseSkeleton)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 1);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 클레이골렘
		if (m_UnitInfo->tSummonSkillCheck.CrayGolem)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 2);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 2, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 골렘마스터리
		if (m_UnitInfo->tSummonSkillCheck.GolemMastery)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 3);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 3, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 스켈레톤메이지
		if (m_UnitInfo->tSummonSkillCheck.RaiseSkeletonMage)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 4);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 4, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 블러드골렘
		if (m_UnitInfo->tSummonSkillCheck.BloodGolem)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 5);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 5, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 서먼레지스트
		if (m_UnitInfo->tSummonSkillCheck.SummonResist)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 6);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 6, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 아이언골렘
		if (m_UnitInfo->tSummonSkillCheck.IronGolem)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 7);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 7, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 파골
		if (m_UnitInfo->tSummonSkillCheck.FireGolem)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 8);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 8, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 리바이브
		if (m_UnitInfo->tSummonSkillCheck.Revive)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"SummonSkill", 9);
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;

			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans, 975 - fCenterX * 2 * 9, 565, 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CStage::Release_Scene()
{
}

CScene * CStage::Create()
{
	CScene* pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CStage::SkillSet()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_LBUTTON))
	{
		if (pt.x > 944 && pt.x < 1006 &&
			pt.y > 659 && pt.y < 715)
		{
			// 플레이어 스킬셋에 추가
			m_bSkillSet = true;
		}

		if (m_bSkillSet)
		{
			// 티쓰
			if (pt.x > 946 && pt.x < 1001 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_TEETH);
				m_dwSkillSet = 0;
				m_bSkillSet = false;
			}

			// 본아머
			if (pt.x > 882 && pt.x < 942 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_BONESHILED);
				m_dwSkillSet = 1;
				m_bSkillSet = false;
			}

			// 포이즌대거
			if (pt.x > 820 && pt.x < 878 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSkillSet = 2;
				m_bSkillSet = false;
			}

			// 시폭
			if (pt.x > 760 && pt.x < 820 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_CORPSEEXPLODEGUTS);
				m_dwSkillSet = 3;
				m_bSkillSet = false;
			}

			// bornwall
			if (pt.x > 699 && pt.x < 755 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSkillSet = 4;
				m_bSkillSet = false;
			}

			// poisonexplosion
			if (pt.x > 635 && pt.x < 693 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_POISONEXPLOSION);
				m_dwSkillSet = 5;
				m_bSkillSet = false;
			}

			// bonespear
			if (pt.x > 576 && pt.x < 630 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_BONESPEAR);
				m_dwSkillSet = 6;
				m_bSkillSet = false;
			}

			// boneprison
			if (pt.x > 513 && pt.x < 569 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSkillSet = 7;
				m_bSkillSet = false;
			}

			// poisonnova
			if (pt.x > 450 && pt.x < 508 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_POISONNOVA);
				m_dwSkillSet = 8;
				m_bSkillSet = false;
			}

			// bonespirit
			if (pt.x > 388 && pt.x < 445 &&
				pt.y > 596 && pt.y < 653)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = true;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_BONESPEAR);
				m_dwSkillSet = 9;
				m_bSkillSet = false;
			}

			// 소환

			// 스켈레톤마스터리
			if (pt.x > 946 && pt.x < 1001 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSummonSkillSet = 0;
				m_bSkillSet = false;
			}

			// 레이즈스켈레톤
			if (pt.x > 882 && pt.x < 942 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_RAISESKELETON);
				m_dwSummonSkillSet = 1;
				m_bSkillSet = false;
			}

			// 클레이골렘
			if (pt.x > 820 && pt.x < 878 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_CLAYGOLEM);
				m_dwSummonSkillSet = 2;
				m_bSkillSet = false;
			}

			// 골렘마스터리
			if (pt.x > 760 && pt.x < 820 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSummonSkillSet = 3;
				m_bSkillSet = false;
			}

			// 레이즈스켈레톤메이지
			if (pt.x > 699 && pt.x < 755 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_RAISESKELETONMAGE);
				m_dwSummonSkillSet = 4;
				m_bSkillSet = false;
			}

			// 블러드골렘
			if (pt.x > 635 && pt.x < 693 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_BLOODGOLEM);
				m_dwSummonSkillSet = 5;
				m_bSkillSet = false;
			}

			// 서먼레지스트
			if (pt.x > 576 && pt.x < 630 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSummonSkillSet = 6;
				m_bSkillSet = false;
			}

			// 아골
			if (pt.x > 513 && pt.x < 569 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSummonSkillSet = 7;
				m_bSkillSet = false;
			}

			// 파골
			if (pt.x > 450 && pt.x < 508 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_FIREGOLEM);
				m_dwSummonSkillSet = 8;
				m_bSkillSet = false;
			}

			// 리바이브
			if (pt.x > 388 && pt.x < 445 &&
				pt.y > 536 && pt.y < 594)
			{
				// 플레이어 스킬셋에 추가
				m_bisSkillType = false;
				dynamic_cast<CNecromancer*>(pPlayer)->Set_UnitSkill(SKILL_END);
				m_dwSummonSkillSet = 9;
				m_bSkillSet = false;
			}
		}
	}
}
