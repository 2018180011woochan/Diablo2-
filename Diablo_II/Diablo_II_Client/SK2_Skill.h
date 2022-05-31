#pragma once

#ifndef __SK2SKILL_H__
#define __SK2SKILL_H__

#include "GameObject.h"
class SK2_Skill final : public CGameObject
{
public:
	explicit SK2_Skill();
private:
	virtual ~SK2_Skill();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create(BULLET _tBullet, _vec3 _SK2Pos);

public:
	_vec3 Get_SK2BulletPos() { return m_tBullet.vPos; }

public:
	void Initialize(BULLET& _tBullet, _vec3 _SK2Pos);

private:
	_vec3		m_vecNecromancerPos;
};

#endif // !__SK2SKILL_H__

