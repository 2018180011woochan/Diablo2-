#pragma once

#ifndef __WRAITH_H__
#define __WRAITH_H__

#include "GameObject.h"
class CWraith final : public CGameObject
{
private:
	explicit CWraith();
public:
	virtual ~CWraith();

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

#endif // !__WRAITH_H__

