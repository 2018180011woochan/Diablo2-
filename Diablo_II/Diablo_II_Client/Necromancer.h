#pragma once

#ifndef __NECROMANCER_H__
#define __NECROMANCER_H__

#include "GameObject.h"
class CGameObject_Manager;
class CNecromancer final : public CGameObject
{
private:
	explicit CNecromancer();
public:
	virtual ~CNecromancer();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Move();
	void Offset();
	void Attack_Skill();
	void Level_Up();
	void Make_BoneSpearEffect(CGameObject* _pObj);

public:
	_vec3 Get_NecromancerPos() { return m_tInfo.vPos; }
	UNITINFO* Get_Necromancer() { return &m_tInfo; }
	int Get_SkeletonCount() { return m_iSkeletonCnt; }
	bool Get_isBloodGolemAlive() { return m_bBloodGolem; }

public:
	void Set_UnitSkill(NECROMANCERSKILL _tSkill) { m_eSkill = _tSkill; }

public:
	static CNecromancer* Create(_vec3 _PlayerPos);

public:
	void Initialize(_vec3 _PlayerPos);

private:
	NECROMANCERSKILL		m_eSkill;

	CGameObject_Manager*	m_pGameObject_Manager;

	bool					m_bisBoneSpearShot;
	float					m_fDeltaTime;

	float					m_fWidth;
	float					m_fHeight;
	float					m_fDistance;

	int						m_iSkeletonCnt;
	bool					m_bBloodGolem;

	bool					m_bisDiabloInit;
	bool					m_bSoundstop;

	float fWidth;
	float fHeight;
	float fDistance;

	_vec3					m_BulletPos;
};

#endif // !__NECROMANCER_H__

