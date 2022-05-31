#pragma once

#ifndef __BONESPEAR_H__
#define __BONESPEAR_H__

#include "GameObject.h"
class CBoneSpear final : public CGameObject
{
private:
	explicit CBoneSpear();
public:
	virtual ~CBoneSpear();

	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Set_Player_Dir(OBJDIR _eDir) { m_eDir = _eDir; }

public:
	static CGameObject* Create(BULLET& _tBullet);

public:
	void Initialize(BULLET& _tBullet);

public:
	_vec3 Get_BoneSpearPos() { return m_tBullet.vPos; }

private:
	_vec3 m_vecMouse;
	float m_fBoneSpearDir;

	OBJDIR m_eDir;


};

#endif // !__BONESPEAR_H__

