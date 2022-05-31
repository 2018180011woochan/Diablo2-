#pragma once

#ifndef __SKILLWINDOW_H__
#define __SKILLWINDOW_H__

#include "GameObject.h"
class CSkillWindow final : public CGameObject
{
private:
	explicit CSkillWindow();
public:
	virtual ~CSkillWindow();

	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Set_SkillWndType(DWORD _dwSkillWndType) { m_dwSkillWndType = _dwSkillWndType; }
	DWORD Get_SkillWndType() { return m_dwSkillWndType; }

public:
	void SkillWndChange();


public:
	static CGameObject* Create();

private:
	DWORD			m_dwSkillWndType;
	UNITINFO*		m_UnitInfo;
	CGameObject*	m_pPlayer;


};

#endif // !__SKILLWINDOW_H__

