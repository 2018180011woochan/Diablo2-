#pragma once

#ifndef __BLOODGOLEM_H__
#define __BLOODGOLEM_H__

#include "GameObject.h"
class CBloodGolem final : public CGameObject
{
private:
	explicit CBloodGolem();
public:
	virtual ~CBloodGolem();

public:
	void ToDiabloMove();

public:
	void Monster_FrameMove(float fSpeed);
	void Monster_DeadFrameMove(float fSpeed);
	void Monster_CreateFrameMove(float fSpeed);

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Initialize(_vec3 MonsterPos);

public:
	static CGameObject* Create(_vec3 MonsterPos);

private:
	_vec3 vecTargetPos;
	PLAYERMONSTER m_tMonster;
	CGameObject* m_pDiablo;
};

#endif // !__BLOODGOLEM_H__

