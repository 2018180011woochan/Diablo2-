#include "stdafx.h"
#include "StartTile.h"


CStartTile::CStartTile()
{
}


CStartTile::~CStartTile()
{
	Release_GameObject();
}

HRESULT CStartTile::LoadStartTile(const wstring & wstrFilePath)
{
	for (auto& pTile : m_vecStartTile)
		Safe_Delete(pTile);
	m_vecStartTile.clear();
	m_vecStartTile.shrink_to_fit();

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
		m_vecStartTile.emplace_back(pTile);
	}
	return S_OK;
}

HRESULT CStartTile::Ready_GameObject()
{
	if (FAILED(LoadStartTile(L"../Data/StartTile.dat")))
	{
		ERR_MSG(L"Load Start Tile Failed");
		return E_FAIL;
	}
	return S_OK;
}

int CStartTile::Update_GameObject()
{
	return OBJ_NOEVENT;
}

void CStartTile::Late_Update_GameObject()
{
}

void CStartTile::Render_GameObject()
{
	_matrix matScale, matTrans, matWrold;

	DWORD dwSize = m_vecStartTile.size();

	for (size_t i = 0; i < dwSize; ++i)
	{
		if (m_vecStartTile[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) > WINCY + TILECY)
			return;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Texture", L"ConturyTile", m_vecStartTile[i]->byDrawID);
		//assert(!(nullptr == pTexInfo));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecStartTile[i]->vSize.x, m_vecStartTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecStartTile[i]->vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_vecStartTile[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWrold = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CStartTile::Release_GameObject()
{
	for (auto& pTile : m_vecStartTile)
		Safe_Delete(pTile);
	m_vecStartTile.clear();
	m_vecStartTile.shrink_to_fit();
}

CGameObject * CStartTile::Create()
{
	CGameObject* pInstance = new CStartTile;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
