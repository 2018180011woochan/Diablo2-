#pragma once

#ifndef __ANIMATIONEFFECTIMPLEMENT_H__
#define __ANIMATIONEFFECTIMPLEMENT_H__

#include "Effect_Implement.h"
class CAnimationEffect_Implement : public CEffect_Implement
{
public:
	explicit CAnimationEffect_Implement();
	virtual ~CAnimationEffect_Implement();

public:
	void Set_StateKey(const wstring& wstrStateKey, const FRAME& rFrame, const float& fSpeed = 1.f);

public:
	// CEffect_Implement을(를) 통해 상속됨
	virtual HRESULT Ready_EffectIMP() override;
	virtual int Update_EffectIMP() override;
	virtual void Render_EffectIMP(const _matrix& rmatWorld) override;
	virtual void Release_EffectIMP() override;

private:
	FRAME m_tFrame;
	float m_fSpeed;
};

#endif // !__ANIMATIONEFFECTIMPLEMENT_H__

