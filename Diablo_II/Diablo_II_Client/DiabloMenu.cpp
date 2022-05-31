#include "stdafx.h"
#include "DiabloMenu.h"
#include "Scene_Manager.h"
#include "SoundMgr.h"

CDiabloMenu::CDiabloMenu()
{
}


CDiabloMenu::~CDiabloMenu()
{
}

HRESULT CDiabloMenu::Ready_Scene()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Intro.wav", CSoundMgr::MENU);
	return S_OK;
}

int CDiabloMenu::Update_Scene()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (pt.x > 423 && pt.x < 854 &&
			pt.y > 250 && pt.y < 288)
		{
			CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENE_STARTMAP);
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MENU);
		}
	}

	return 0;
}

void CDiabloMenu::Late_Update_Scene()
{
}

void CDiabloMenu::Render_Scene()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Menu");
	if (pTexInfo == nullptr)
		return;

	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX >> 1, WINCY >> 1, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDiabloMenu::Release_Scene()
{
}

CScene * CDiabloMenu::Create()
{
	CScene* pInstance = new CDiabloMenu;
	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
