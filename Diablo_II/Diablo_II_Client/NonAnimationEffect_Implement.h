#pragma once

#ifndef __NONANIMATIONEFFECTIMPLEMENT_H__
#define __NONANIMATIONEFFECTIMPLEMENT_H__

#include "Effect_Implement.h"
class CNonAnimationEffect_Implement final : public CEffect_Implement
{
public:
	explicit CNonAnimationEffect_Implement();
	virtual ~CNonAnimationEffect_Implement();

public:
	void Set_StataKey(const wstring& wstrStateKey, const float& fLimitTime = 5.f);

public:
	// CEffect_Implement을(를) 통해 상속됨
	virtual HRESULT Ready_EffectIMP() override;
	virtual int Update_EffectIMP() override;
	virtual void Render_EffectIMP(const _matrix & rmatWorld) override;
	virtual void Release_EffectIMP() override;

private:
	float m_fLimitTime;
	float m_fCountTime;
};

#endif // !__NONANIMATIONEFFECTIMPLEMENT_H__
