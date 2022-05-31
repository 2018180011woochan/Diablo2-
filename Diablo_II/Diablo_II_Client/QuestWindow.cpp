#include "stdafx.h"
#include "QuestWindow.h"
#include "Key_Manager.h"

CQuestWindow::CQuestWindow()
	: m_bisDiabloDead(false)
{
}


CQuestWindow::~CQuestWindow()
{
	Release_GameObject();
}

HRESULT CQuestWindow::Ready_GameObject()
{
	m_tFrame = { 0.f, 26.f };
	return S_OK;
}

int CQuestWindow::Update_GameObject()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (bisOpenQuestWnd == false)
		return OBJ_DEAD;


	if (CKey_Manager::Get_Instance()->Key_Down(KEY_LBUTTON))
	{
		if (bisOpenQuestWnd)
		{
			// out
			if (pt.x > 539 && pt.x < 572 &&
				pt.y > 521 && pt.y < 554)
			{
				bisOpenQuestWnd = false;
			}
		}
	}

	return OBJ_NOEVENT;
}

void CQuestWindow::Late_Update_GameObject()
{
	QuestFrameMove(0.3f);
}

void CQuestWindow::Render_GameObject()
{
	TCHAR szPlayer_Strength[MAX_PATH] = L"";
	wchar_t wstring[] = L"µð¾Æºí·Î¸¦ ¹«Âñ·¯ ÁÖ¼¼¿ä";

	swprintf_s(szPlayer_Strength, __T("%ls"), wstring);

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Window", 10);
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX - fCenterX - 700, WINCY - fCenterY - 150, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Äù½ºÆ® ³»¿ë
	RECT rPoint = { -155, 55, 265, 215 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Strength, lstrlen(szPlayer_Strength), &rPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	//////////////Äù½ºÆ® ¹îÁö
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Quest2", 0);
	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	//_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX - fCenterX - 1000, WINCY - fCenterY - 550, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (bisDiabloDead)
	{
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Quest2", m_tFrame.fStartFrame);
		fCenterX = pTexInfo->tImageInfo.Width >> 1;
		fCenterY = pTexInfo->tImageInfo.Height >> 1;

		//_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, WINCX - fCenterX - 1000, WINCY - fCenterY - 550, 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CQuestWindow::Release_GameObject()
{
}

void CQuestWindow::QuestFrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		m_tFrame.fStartFrame = 25.f;
}

CGameObject * CQuestWindow::Create()
{
	CGameObject* pInstance = new CQuestWindow;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
