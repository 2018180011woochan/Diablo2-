#include "stdafx.h"
#include "AnimationEffect_Implement.h"


CAnimationEffect_Implement::CAnimationEffect_Implement()
{
}


CAnimationEffect_Implement::~CAnimationEffect_Implement()
{
}

void CAnimationEffect_Implement::Set_StateKey(const wstring & wstrStateKey, const FRAME & rFrame, const float & fSpeed)
{
	m_wstrStateKey = wstrStateKey;
	m_tFrame = rFrame;
	m_fSpeed = fSpeed;
}

HRESULT CAnimationEffect_Implement::Ready_EffectIMP()
{
	return S_OK;
}

int CAnimationEffect_Implement::Update_EffectIMP()
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * m_fSpeed;
	if (m_tFrame.fStartFrame >= m_tFrame.fEndFrame)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CAnimationEffect_Implement::Render_EffectIMP(const _matrix& rmatWorld)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_wstrStateKey, DWORD(m_tFrame.fStartFrame));
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&rmatWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CAnimationEffect_Implement::Release_EffectIMP()
{
}
