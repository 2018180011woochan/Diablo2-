#pragma once

#ifndef __GROUNDFIRE_H__
#define __GROUNDFIRE_H__

#include "GameObject.h"
class CGroundFire final : public CGameObject
{
private:
	explicit CGroundFire();
public:
	virtual ~CGroundFire();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Breath_Update(float fSpeed);

public:
	static CGameObject* Create(BULLET& _tBullet, _vec3 _Diapos);

public:
	void Initialize(BULLET& _tBullet, _vec3 _Diapos);

private:
	_vec3 m_vecNecromancerPos;
};

#endif // !__GROUNDFIRE_H__

