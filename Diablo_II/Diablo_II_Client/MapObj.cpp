#include "stdafx.h"
#include "MapObj.h"


CMapObj::CMapObj()
{
}


CMapObj::~CMapObj()
{
	Release_GameObject();
}

HRESULT CMapObj::Load_MapObject(const wstring & wstrFilePath)
{
	for (auto& pMapObj : m_vecMapObject)
		Safe_Delete(pMapObj);
	m_vecMapObject.clear();
	m_vecMapObject.shrink_to_fit();

	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	OBJECT* pMapObj = nullptr;
	while (true)
	{
		pMapObj = new OBJECT;
		ReadFile(hFile, pMapObj, sizeof(OBJECT), &dwByte, nullptr);
		if (0 == dwByte)
		{
			Safe_Delete(pMapObj);
			break;
		}
		m_vecMapObject.emplace_back(pMapObj);
	}
	return S_OK;
}

HRESULT CMapObj::Ready_GameObject()
{
	if (FAILED(Load_MapObject(L"../Data/MapObjSaveTest.dat")))
	{
		ERR_MSG(L"Load Stage Object Failed");
		return E_FAIL;
	}
	return S_OK;
}

int CMapObj::Update_GameObject()
{
	return 0;
}

void CMapObj::Late_Update_GameObject()
{
}

void CMapObj::Render_GameObject()
{
	_matrix matScale, matTrans, matWorld;

	DWORD dwSize = m_vecMapObject.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Object", L"Object", m_vecMapObject[i]->byDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecMapObject[i]->vSize.x, m_vecMapObject[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecMapObject[i]->vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_vecMapObject[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMapObj::Release_GameObject()
{
	for (auto& pMapObj : m_vecMapObject)
		Safe_Delete(pMapObj);
	m_vecMapObject.clear();
	m_vecMapObject.shrink_to_fit();
}

CGameObject * CMapObj::Create()
{
	CGameObject* pInstance = new CMapObj;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
