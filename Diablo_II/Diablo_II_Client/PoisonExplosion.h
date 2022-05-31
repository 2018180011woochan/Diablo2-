#pragma once

#ifndef __POISONEXPLOSION_H__
#define __POISONEXPLOSION_H__

#include "GameObject.h"
class CPoisonExplosion final : public CGameObject
{
public:
	explicit CPoisonExplosion();
	virtual ~CPoisonExplosion();

	// CGameObject을(를) 통해 상속됨
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
	void PoisonExplosion_FrameMove(float fSpeed);
};

#endif // !__POISONEXPLOSION_H__

