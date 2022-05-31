#pragma once

#ifndef __BUFFEFFECT_H__
#define __BUFFEFFECT_H__

#include "Effect.h"
class CBuffEffect final : public CEffect
{
public:
	explicit CBuffEffect(CEffect_Implement* pBridge);
	virtual ~CBuffEffect();

public:
	// CEffect을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
};

#endif // !__BUFFEFFECT_H__

