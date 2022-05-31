#include "stdafx.h"
#include "BuffEffect.h"
#include "Effect_Implement.h"
#include "GameObject_Manager.h"

CBuffEffect::CBuffEffect(CEffect_Implement* pBridge)
	:CEffect(pBridge)
{
}


CBuffEffect::~CBuffEffect()
{
}

HRESULT CBuffEffect::Ready_GameObject()
{
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vPos = { 100.f, 0.f, 0.f };

	return S_OK;
}

int CBuffEffect::Update_GameObject()
{
	m_fAngle += 45.f * CTime_Manager::Get_Instance()->Get_TimeDelta();
	return m_pBridge->Update_EffectIMP();
}

void CBuffEffect::Late_Update_GameObject()
{
}

void CBuffEffect::Render_GameObject()
{
	_matrix matScale, matTrans, matRotZ, matRevRotZ, matParent;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRevRotZ, D3DXToRadian(m_fAngle));
	_vec3 vParent = CGameObject_Manager::Get_Instance()->Get_Player()->Get_Pos();
	D3DXMatrixTranslation(&matParent, vParent.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), vParent.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

	matScale *= matRotZ * matTrans * matRevRotZ * matParent;


	m_pBridge->Render_EffectIMP(matScale);
}
