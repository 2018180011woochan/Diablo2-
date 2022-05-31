#include "stdafx.h"
#include "NonAnimationEffect_Implement.h"


CNonAnimationEffect_Implement::CNonAnimationEffect_Implement()
	:m_fLimitTime(0.f)
	, m_fCountTime(0.f)
{
}


CNonAnimationEffect_Implement::~CNonAnimationEffect_Implement()
{
}

void CNonAnimationEffect_Implement::Set_StataKey(const wstring & wstrStateKey, const float & fLimitTime)
{
	m_wstrStateKey = wstrStateKey;
	m_fLimitTime = fLimitTime;
}

HRESULT CNonAnimationEffect_Implement::Ready_EffectIMP()
{
	return S_OK;
}

int CNonAnimationEffect_Implement::Update_EffectIMP()
{
	m_fCountTime += CTime_Manager::Get_Instance()->Get_TimeDelta();
	if (m_fCountTime >= m_fLimitTime)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CNonAnimationEffect_Implement::Render_EffectIMP(const _matrix & rmatWorld)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_wstrStateKey, 0);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&rmatWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CNonAnimationEffect_Implement::Release_EffectIMP()
{
}
