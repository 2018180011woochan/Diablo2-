#pragma once

#ifndef __SK2SKILLEFFECT_H__
#define __SK2SKILLEFFECT_H__

#include "GameObject.h"
class CSK2SkillEffect final : public CGameObject
{
private:
	explicit CSK2SkillEffect();
public:
	virtual ~CSK2SkillEffect();

public:
	void Effect_FrameMove(float fSpeed);

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create(EFFECT _tEffect, _vec3 _SK2BulletPos);

public:
	void Initialize(EFFECT _tEffect, _vec3 _SK2BulletPos);

private:
	_vec3		m_SK2BulletPos;
};

#endif // !__SK2SKILLEFFECT_H__

