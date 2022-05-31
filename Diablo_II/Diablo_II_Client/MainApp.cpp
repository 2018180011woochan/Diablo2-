#include "stdafx.h"
#include "MainApp.h"
#include "GameObject_Manager.h"
#include "Scene_Manager.h"
#include "Frame_Manager.h"
#include "Key_Manager.h"
#include "SoundMgr.h"

CMainApp::CMainApp()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
	, m_pScene_Manager(CScene_Manager::Get_Instance())
	, m_pKey_Manager(CKey_Manager::Get_Instance())
{
}

HRESULT CMainApp::Ready_MainApp()
{
	//m_tFrame = { 0.f, 10.f };

	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device(CGraphic_Device::MODE_WIN)))
		goto SYSTEM_ERR;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Loading/Load/%d.png", L"Loading", L"Load", 10)))
		goto SYSTEM_ERR;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Menu/0.png", L"Menu")))
		goto SYSTEM_ERR;
	if (FAILED(CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENE_LOADING)))
		goto SYSTEM_ERR;
	if (FAILED(CTime_Manager::Get_Instance()->Ready_TimeManager()))
		goto SYSTEM_ERR;

	CSoundMgr::Get_Instance()->Initialize();
	return S_OK;



SYSTEM_ERR:
	ERR_MSG(L"Ready Failed - MainApp.cpp");
	return E_FAIL;
}

void CMainApp::Update_MainApp()
{
	CTime_Manager::Get_Instance()->Compute_TimeManager();
	m_pScene_Manager->Update_SceneManager();
	CKey_Manager::Get_Instance()->Key_Update();
}

void CMainApp::LateUpdate_MainApp()
{
	m_pScene_Manager->Late_Update_SceneManager();
	m_pScroll_Manager->Scroll_Lock();
}

void CMainApp::Render_MainApp(CFrame_Manager* pFrameManager)
{
	m_pGraphic_Device->Render_Begin();
	m_pScene_Manager->Render_SceneManager();
	pFrameManager->RenderFPS();
	m_pGraphic_Device->Render_End();
}

void CMainApp::Release_MainApp()
{
	CTime_Manager::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	m_pGameObject_Manager->Destroy_Instance();
	m_pScene_Manager->Destroy_Instance();
	m_pGraphic_Device->Destroy_Instance();
	m_pKey_Manager->Destroy_Instance();
	CSoundMgr::Destroy_Instance();
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		return nullptr;
	}
	return pInstance;
}

void CMainApp::Free()
{
	Release_MainApp();
}


