#include "stdafx.h"
#include "StartMapObj.h"


CStartMapObj::CStartMapObj()
{
}


CStartMapObj::~CStartMapObj()
{
	Release_GameObject();
}

HRESULT CStartMapObj::Load_StartMapObject(const wstring & wstrFilePath)
{
	for (auto& pMapObj : m_vecStartMapObject)
		Safe_Delete(pMapObj);
	m_vecStartMapObject.clear();
	m_vecStartMapObject.shrink_to_fit();

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
		m_vecStartMapObject.emplace_back(pMapObj);
	}
	return S_OK;
}

HRESULT CStartMapObj::Ready_GameObject()
{
	if (FAILED(Load_StartMapObject(L"../Data/StartObjSave.dat")))
	{
		ERR_MSG(L"Load Start Object Failed");
		return E_FAIL;
	}
	return S_OK;
}

int CStartMapObj::Update_GameObject()
{
	return OBJ_NOEVENT;
}

void CStartMapObj::Late_Update_GameObject()
{
}

void CStartMapObj::Render_GameObject()
{
	_matrix matScale, matTrans, matWorld;

	DWORD dwSize = m_vecStartMapObject.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Texture", L"struct", m_vecStartMapObject[i]->byDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecStartMapObject[i]->vSize.x, m_vecStartMapObject[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecStartMapObject[i]->vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_vecStartMapObject[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CStartMapObj::Release_GameObject()
{
	for (auto& pMapObj : m_vecStartMapObject)
		Safe_Delete(pMapObj);
	m_vecStartMapObject.clear();
	m_vecStartMapObject.shrink_to_fit();
}

CGameObject * CStartMapObj::Create()
{
	CGameObject* pInstance = new CStartMapObj;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
