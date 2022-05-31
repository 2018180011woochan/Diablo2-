#pragma once

#ifndef __STAGE_H__
#define __STAGE_H__
#include "Scene.h"

class CGameObject_Manager;
class CGameObject;
class CStage final : public CScene
{
private:
	explicit CStage();
public:
	virtual ~CStage();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual int Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	static CScene* Create();

public:
	void SkillSet();

private:
	CGameObject_Manager*	m_pGameObject_Manager;

	CGameObject*			pSkillWnd;
	CGameObject*			pStatWnd;
	CGameObject*			pQuestWnd;
		
	CGameObject*			pPlayer;
	UNITINFO*				m_UnitInfo;

	bool					m_bSkillSet;
	DWORD					m_dwSkillSet;
	DWORD					m_dwSummonSkillSet;

	bool					m_bisSkillType;

	CGameObject*			pDiablo;
};

#endif __STAGE_H__

