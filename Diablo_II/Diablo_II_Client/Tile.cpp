#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release_GameObject();
}

HRESULT CTile::LoadTile(const wstring & wstrFilePath)
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	TILE* pTile = nullptr;
	while (true)
	{
		pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}
		m_vecTile.emplace_back(pTile);
	}
	return S_OK;
}

HRESULT CTile::Ready_GameObject()
{
	if (FAILED(LoadTile(L"../Data/SaveTest.dat")))
	{
		ERR_MSG(L"Load Stage Tile Failed");
		return E_FAIL;
	}
	return S_OK;
}

int CTile::Update_GameObject()
{
	//float fTimeDelta = CTime_Manager::Get_Instance()->Get_TimeDelta();
	//float fSpeed = 500.f * fTimeDelta;
	//if (GetAsyncKeyState(VK_LEFT))
	//	CScroll_Manager::Set_Scroll({ -fSpeed, 0.f, 0.f });
	//if (GetAsyncKeyState(VK_RIGHT))
	//	CScroll_Manager::Set_Scroll({ fSpeed, 0.f, 0.f });
	//if (GetAsyncKeyState(VK_UP))
	//	CScroll_Manager::Set_Scroll({ 0.f,-fSpeed, 0.f });
	//if (GetAsyncKeyState(VK_DOWN))
	//	CScroll_Manager::Set_Scroll({ 0.f,fSpeed, 0.f });
	return 0;
}

void CTile::Late_Update_GameObject()
{

}

void CTile::Render_GameObject()
{
	_matrix matScale, matTrans, matWrold;

	DWORD dwSize = m_vecTile.size();

	for (size_t i = 0; i < dwSize; ++i)
	{
		if (m_vecTile[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) > WINCY + TILECY)
			return;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		//assert(!(nullptr == pTexInfo));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_vecTile[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWrold = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTile::Release_GameObject()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

CGameObject * CTile::Create()
{
	CGameObject* pInstance = new CTile;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
