#include "stdafx.h"
#include "Loading.h"
#include "Scene_Manager.h"

CLoading::CLoading()
{
}


CLoading::~CLoading()
{
}

HRESULT CLoading::Ready_Scene()
{
	m_tFrame = { 0.f, 10.f };
	InitializeCriticalSection(&m_Critical_Section);
	
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, CLoading::ImageLoadFunc, this, 0, nullptr);
	return S_OK;
}

int CLoading::Update_Scene()
{
	FrameMove(0.1f);
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		DeleteCriticalSection(&m_Critical_Section);
		CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENE_MENU);
		return 0;
	}
	return 0;
}

void CLoading::Late_Update_Scene()
{
}

void CLoading::Render_Scene()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Loading", L"Load", DWORD(m_tFrame.fStartFrame));
	if (nullptr == pTexInfo)
		return;

	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;
	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX >> 1, WINCY >> 1, 0.f);
	matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLoading::Release_Scene()
{
}

unsigned int CLoading::ImageLoadFunc(LPVOID pArgment)
{
	CLoading* pLoading = reinterpret_cast<CLoading*>(pArgment);
	EnterCriticalSection(&pLoading->m_Critical_Section);
	// ÄÚµå 
	if (FAILED(CTexture_Manager::Get_Instance()->LoadImagePath(L"../Data/PathInfo.txt")))
	{
		ERR_MSG(L"Tile Image Insert Failed");
		return E_FAIL;
	}
	LeaveCriticalSection(&pLoading->m_Critical_Section);
	return 0;
}

CScene * CLoading::Create()
{
	CScene* pInstance = new CLoading;
	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CLoading::FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		m_tFrame.fStartFrame = 0.f;
}
