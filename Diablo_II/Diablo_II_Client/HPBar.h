#pragma once

#ifndef __HPBAR_H__
#define __HPBAR_H__

#include "GameObject.h"
class CHPBar final : public CGameObject
{
private:
	explicit CHPBar();
public:
	virtual ~CHPBar();

	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();

private:
	int				m_iHP;

	UNITINFO*		m_UnitInfo;
	CGameObject*	m_pPlayer;
};

#endif // !__HPBAR_H__

