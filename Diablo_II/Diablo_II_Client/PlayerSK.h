#pragma once

#ifndef __PLAYERSK_H__
#define __PLAYERSK_H__

#include "GameObject.h"
class CPlayerSK final : public CGameObject
{
private:
	explicit CPlayerSK();
public:
	virtual ~CPlayerSK();

public:
	void Move(_vec3 _vecTarget);
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
	void Initialize( _vec3 MonsterPos);

public:
	static CGameObject* Create( _vec3 MonsterPos);

private:
	_vec3 vecTargetPos;
	//list<CGameObject*>& _m_listMonster;
	list<CGameObject*> _m_listMonster;
	float fCurDistance;
	CGameObject* m_pDiablo;
};

#endif // !__PLAYERSK_H__

