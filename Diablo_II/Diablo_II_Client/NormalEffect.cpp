#include "stdafx.h"
#include "NormalEffect.h"
#include "Effect_Implement.h"

CNormalEffect::CNormalEffect(CEffect_Implement* pBridge)
	: CEffect(pBridge)
{
}


CNormalEffect::~CNormalEffect()
{
}

HRESULT CNormalEffect::Ready_GameObject()
{
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	return S_OK;
}

int CNormalEffect::Update_GameObject()
{
	return m_pBridge->Update_EffectIMP();
}

void CNormalEffect::Late_Update_GameObject()
{
}

void CNormalEffect::Render_GameObject()
{
	_matrix matScale, matTrans;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
	matScale *= matTrans;

	m_pBridge->Render_EffectIMP(matScale);
}
