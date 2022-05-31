#include "stdafx.h"
#include "StartObj.h"
#include "Diablo_II_MapToolView.h"

CStartObj::CStartObj()
{
}


CStartObj::~CStartObj()
{
	Release();
}

HRESULT CStartObj::Ready_Object()
{
	m_vecObject.reserve(TILEX * TILEY);
	return S_OK;
}

void CStartObj::Render_Object()
{
	_matrix matScale, matTrans, matWrold, matRatio;

	DWORD dwSize = m_vecObject.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Texture", L"struct", m_vecObject[i]->byDrawID);
		assert(!(nullptr == pTexInfo));
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecObject[i]->vSize.x, m_vecObject[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecObject[i]->vPos.x - m_pView->GetScrollPos(0), m_vecObject[i]->vPos.y - m_pView->GetScrollPos(1), 0.f);
		matWrold = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CStartObj::Release()
{
	for (auto& pObj : m_vecObject)
		Safe_Delete(pObj);
	m_vecObject.clear();
	m_vecObject.shrink_to_fit();
}

void CStartObj::Obj_Insert(const _vec3 & vPos, const BYTE & byDrawID)
{
	if (byDrawID == 99)
		return;
	OBJECT* pObj = new OBJECT;
	pObj->vPos = vPos;
	pObj->vSize = { 1.f, 1.f, 0.f };
	pObj->byDrawID = byDrawID;

	m_vecObject.emplace_back(pObj);
}

void CStartObj::Delete_Obj()
{
	if (m_vecObject.size() == 0)
		return;
	m_vecObject.pop_back();
	m_vecObject.shrink_to_fit();
}
