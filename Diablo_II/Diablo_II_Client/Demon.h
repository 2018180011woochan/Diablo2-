#pragma once

#ifndef __DEMON_H__
#define __DEMON_H__

#include "GameObject.h"
class CDemon final : public CGameObject
{
private:
	explicit CDemon();
public:
	virtual ~CDemon();

public:
	void Move();

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
};

#endif // !__DEMON_H__

