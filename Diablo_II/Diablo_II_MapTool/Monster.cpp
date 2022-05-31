#include "stdafx.h"
#include "Monster.h"
#include "Diablo_II_MapToolView.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

HRESULT CMonster::Ready_Object()
{
	m_vecMonster.reserve(50);
	return S_OK;
}

void CMonster::Render_Object()
{
	_matrix matScale, matTrans, matWrold, matRatio;

	DWORD dwSize = m_vecMonster.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Monster", L"Sample", m_vecMonster[i]->byMonsterID);
		assert(!(nullptr == pTexInfo));
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecMonster[i]->vSize.x, m_vecMonster[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecMonster[i]->vPos.x - m_pView->GetScrollPos(0), m_vecMonster[i]->vPos.y - m_pView->GetScrollPos(1), 0.f);
		matWrold = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CMonster::Release()
{
	for (auto& pObj : m_vecMonster)
		Safe_Delete(pObj);
	m_vecMonster.clear();
	m_vecMonster.shrink_to_fit();
}

void CMonster::Obj_Insert(const _vec3 & vPos, const BYTE & byDrawID)
{
	MONSTER* pObj = new MONSTER;
	pObj->vPos = vPos;
	pObj->vSize = { 1.f, 1.f, 0.f };
	pObj->byMonsterID = byDrawID;

	m_vecMonster.emplace_back(pObj);
}

void CMonster::Delete_Obj()
{
	if (m_vecMonster.size() == 0)
		return;
	m_vecMonster.pop_back();
	m_vecMonster.shrink_to_fit();
}
