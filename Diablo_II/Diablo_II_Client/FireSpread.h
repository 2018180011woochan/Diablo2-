#pragma once

#ifndef __FIRESPREAD_H__
#define __FIRESPREAD_H__

#include "GameObject.h"
class CFireSpread final : public CGameObject
{
public:
	explicit CFireSpread();
	virtual ~CFireSpread();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create(BULLET& _tBullet, _vec3 _BulletDir);

public:
	void Initialize(BULLET& _tBullet, _vec3 _BulletDir);
};

#endif // !__FIRESPREAD_H__

