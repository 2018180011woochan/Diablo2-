#pragma once

#ifndef __DIABLO_H__
#define __DIABLO_H__

#include "GameObject.h"
class CDiablo final : public CGameObject
{
private:
	explicit CDiablo();
public:
	virtual ~CDiablo();

public:
	void Move();
	void Run();
	void Skill();
	void Monster_FrameMove(float fSpeed);
	void Monster_FireSpreadFrameMove(float fSpeed);
	void Monster_DeadFrameMove(float fSpeed);
	void Monster_BreathFrameMove(float fSpeed);
	void Monster_GroundFireFrameMove(float fSpeed);

public:
	_vec3 Get_DiabloPos() { return m_tMonster.vPos; }
	bool Get_isDiabloDead() { return m_bisDiabloDead; }

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Initialize(MONSTER& _tMonster);

public:
	static CGameObject* Create(MONSTER& _tMonster);

private:
	float m_dwSkillTime;
	bool  m_bisDiabloDead;
	OBJSTATE m_eCurrentObjstate;
};

#endif // !__DIABLO_H__

