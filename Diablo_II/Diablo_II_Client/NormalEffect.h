#pragma once

#ifndef __NORMALEFFECT_H__
#define __NORMALEFFECT_H__

#include "Effect.h"
class CNormalEffect final : public CEffect
{
public:
	explicit CNormalEffect(CEffect_Implement* pBridge);
	virtual ~CNormalEffect();

public:
	// CEffect을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
};

#endif // !__NORMALEFFECT_H__

