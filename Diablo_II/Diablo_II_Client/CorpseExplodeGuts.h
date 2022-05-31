#pragma once

#ifndef __CORPSEEXPLODEGUTS_H__
#define __CORPSEEXPLODEGUTS_H__

#include "GameObject.h"
class CCorpseExplodeGuts final : public CGameObject
{
public:
	explicit CCorpseExplodeGuts();
	virtual ~CCorpseExplodeGuts();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create(BULLET& _tBullet);

public:
	void Initialize(BULLET& _tBullet);

public:
	void CorpseExplodeGuts_FrameMove(float fSpeed);
};

#endif // !__CORPSEEXPLODEGUTS_H__
