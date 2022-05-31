#pragma once

#ifndef __STATWINDOW_H__
#define __STATWINDOW_H__

#include "GameObject.h"
class CNecromancer;
class CStatWindow final : public CGameObject
{
private:
	explicit CStatWindow();
public:
	virtual ~CStatWindow();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();

public:
	void Change_StatWnd(UNITINFO* _tUnitInfo);

public:
	void Set_UnitInfo(UNITINFO* _pUnitInfo) { m_UnitInfo = _pUnitInfo; }

private:
	UNITINFO*		m_UnitInfo;
	CGameObject*	m_pPlayer;
};

#endif // !__STATWINDOW_H__

