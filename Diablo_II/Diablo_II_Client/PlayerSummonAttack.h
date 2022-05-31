#pragma once

#ifndef __PLAYERSUMMONATTACK_H__
#define __PLAYERSUMMONATTACK_H__

#include "GameObject.h"
class CPlayerSummonAttack final : public CGameObject
{
private:
	explicit CPlayerSummonAttack();
public:
	virtual ~CPlayerSummonAttack();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create(BULLET& _tBullet, _vec3 _MonsterPos, float _fAttack);

public:
	void Initialize(BULLET& _tBullet, _vec3 _MonsterPos, float _fAttack);

private:
	_vec3		m_vecDiaPos;
};

#endif // !__PLAYERSUMMONATTACK_H__

