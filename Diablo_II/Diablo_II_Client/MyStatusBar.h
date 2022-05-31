#pragma once

#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

#include "GameObject.h"
class CMyStatusBar final : public CGameObject
{
private:
	explicit CMyStatusBar();
public:
	virtual ~CMyStatusBar();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();

private:
	vector<UI*>		m_vecUI;
	int				m_iStamina;
	int				m_iExpBar;

	UNITINFO*		m_UnitInfo;
	CGameObject*	m_pPlayer;

	bool			m_bStatLightUp;
};

#endif // !__STATUSBAR_H__

