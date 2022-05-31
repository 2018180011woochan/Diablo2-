#pragma once

#ifndef __BONESPEAREFFECT_H__
#define __BONESPEAREFFECT_H__

#include "GameObject.h"
class CBoneSpearEffect final : public CGameObject
{
public:
	explicit CBoneSpearEffect();
	virtual ~CBoneSpearEffect();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Set_Player_Dir(OBJDIR _eDir) { m_eDir = _eDir; }
	void Set_SkillIndex(int _iSkillIndex) { m_iSkillIndex = _iSkillIndex; }
	void Set_MousePos(_vec3 _Mouse) { m_vecMouse = _Mouse; }

public:
	_vec3 Get_BoneSpearPos() { return m_tBullet.vPos; }

public:
	void Update_Dir();

public:
	static CGameObject* Create(int _iSkillIndex, _vec3 _Mouse);

private:
	_vec3		m_vecMouse;

	OBJDIR		m_eDir;
	int			m_iSkillIndex;
	float		m_fBoneSpearDir;


};

#endif // !__BONESPEAREFFECT_H__

