#pragma once

#ifndef __POISONNOVA_H__
#define __POISONNOVA_H__

#include "GameObject.h"
class CPoisonNova final : public CGameObject
{
public:
	explicit CPoisonNova();
	virtual ~CPoisonNova();

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

#endif // !__POISONNOVA_H__

