#pragma once

#ifndef __MPBAR_H__
#define __MPBAR_H__

#include "GameObject.h"
class CMPBar final : public CGameObject
{
public:
	CMPBar();
	virtual ~CMPBar();

	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();

private:
	int				m_iMP;

	UNITINFO*		m_UnitInfo;
	CGameObject*	m_pPlayer;
};

#endif // !__MPBAR_H__

