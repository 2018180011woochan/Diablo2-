#pragma once

#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "GameObject.h"
class CEffect_Implement;
class CEffect abstract : public CGameObject
{
public:
	explicit CEffect(CEffect_Implement* pBridge);
	virtual ~CEffect();

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() PURE;
	virtual int Update_GameObject() PURE;
	virtual void Late_Update_GameObject() PURE;
	virtual void Render_GameObject() PURE;
	virtual void Release_GameObject() override;

protected:
	CEffect_Implement* m_pBridge;
};

#endif // !__EFFECT_H__

