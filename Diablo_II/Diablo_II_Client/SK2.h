#pragma once

#ifndef __SK2_H__
#define __SK2_H__

#include "GameObject.h"
class CGameObject_Manager;
class CSK2 final : public CGameObject
{
private:
	explicit CSK2();
public:
	virtual ~CSK2();

public:
	void Move();
	void Attack();

public:
	_vec3 Get_SK2_Pos() { return m_tMonster.vPos; }

public:
	void Monster_FrameMove(float fSpeed);
	void Monster_DeadFrameMove(float fSpeed);

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
	CGameObject_Manager* m_pGameObject_Manager;
};

#endif // !__SK2_H__

