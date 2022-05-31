#include "stdafx.h"
#include "StartMap.h"
#include "GameObject_Manager.h"
#include "Key_Manager.h"
#include "StartTile.h"
#include "StartMapObj.h"
#include "Necromancer.h"
#include "Scene_Manager.h"
#include "HarryCain.h"
#include "QuestWindow.h"
#include "Potal.h"
// UI //
#include "MyStatusBar.h"
#include "HPBar.h"
#include "MPBar.h"

#include "SoundMgr.h"

CStartMap::CStartMap()
	: m_pGameObject_Manager(CGameObject_Manager::Get_Instance()),
	 pPlayer(nullptr), pHarryCain(nullptr), m_bisPotal(false), pPotal(nullptr)
{
	ZeroMemory(&rHarryCainRect, sizeof(rHarryCainRect));
	ZeroMemory(&rPortalRect, sizeof(rPortalRect));
}


CStartMap::~CStartMap()
{
	Release_Scene();
}

HRESULT CStartMap::Ready_Scene()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Back.wav");



	pTile = CStartTile::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_STARTTILE, pTile);

	pMapObj = CStartMapObj::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_STARTMAPOBJ, pMapObj);

	CGameObject* pMyStatusBar = CMyStatusBar::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pMyStatusBar);

	pMyStatusBar = CHPBar::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pMyStatusBar);

	pMyStatusBar = CMPBar::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pMyStatusBar);

	_vec3 PlayerPos = { 700.f ,500.f, 0.f };

	pPlayer = CNecromancer::Create(PlayerPos);
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_PLAYER, pPlayer);

	CGameObject* pHarryCain = CHarryCain::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_HARRYCAIN, pHarryCain);

	//CGameObject* pPotal = CPotal::Create();
	//m_pGameObject_Manager->Add_GameObject_Manager(OBJ_POTAL, pPotal);

	return S_OK;
}

int CStartMap::Update_Scene()
{
	pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(pPlayer)->Get_Necromancer();

	pHarryCain = CGameObject_Manager::Get_Instance()->Get_HarryCain();
	rHarryCainRect = dynamic_cast<CHarryCain*>(pHarryCain)->Get_HarryCainRect();

	

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	_vec3 vMouse = { pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f };

	rMouseRect.top = vMouse.y - 20;
	rMouseRect.left = vMouse.x - 20;
	rMouseRect.bottom = vMouse.y + 20;
	rMouseRect.right = vMouse.x + 20;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		RECT rc = {};
		if (IntersectRect(&rc, &rMouseRect, &rHarryCainRect))
		{
			bisOpenQuestWnd = true;
			pQuestWnd = CQuestWindow::Create();
			m_pGameObject_Manager->Add_GameObject_Manager(OBJ_UI, pQuestWnd);

			dynamic_cast<CHarryCain*>(pHarryCain)->Set_QuestAccess();
			m_bisPotal = true;
		}
	}

	if (!(pPotal == nullptr))
	{
		pPotal = CGameObject_Manager::Get_Instance()->Get_Portal();
		rPortalRect = dynamic_cast<CPotal*>(pPotal)->Get_PortalRect();

		RECT rc = {};
		if (IntersectRect(&rc, &rMouseRect, &rPortalRect))
		{
			dynamic_cast<CPotal*>(pPotal)->SetFont();
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (IntersectRect(&rc, &rMouseRect, &rPortalRect))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"PortalEnter.wav", CSoundMgr::POTALENTER);
				CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENE_STAGE);
				return OBJ_NOEVENT;
			}
		}
	}

	if (m_bisPotal)
	{
		pPotal = CPotal::Create();
		CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", CSoundMgr::POTAL);
		m_pGameObject_Manager->Add_GameObject_Manager(OBJ_POTAL, pPotal);
		m_bisPotal = false;
	}

	m_pGameObject_Manager->Update_GameObject_Manager();
	return OBJ_NOEVENT;
}

void CStartMap::Late_Update_Scene()
{
	m_pGameObject_Manager->Late_Update_GameObject_Manager();

	if (GetAsyncKeyState(VK_SPACE))
	{
		CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENE_STAGE);
	}
}

void CStartMap::Render_Scene()
{
	m_pGameObject_Manager->Render_GameObject_Manager();
}

void CStartMap::Release_Scene()
{
	//pTile->Release_GameObject();
	//pMapObj->Release_GameObject();
	//pPlayer->Release_GameObject();

	m_pGameObject_Manager->Release_GameObject_Manager();
}

CScene * CStartMap::Create()
{
	CScene* pInstance = new CStartMap;
	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
