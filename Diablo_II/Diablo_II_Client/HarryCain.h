#pragma once

#ifndef __HARRYCAIN_H__
#define __HARRYCAIN_H__

#include "GameObject.h"
class CHarryCain final : public CGameObject
{
private:
	explicit CHarryCain();
	virtual ~CHarryCain();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	RECT Get_HarryCainRect() { return m_tRect; }

public:
	void Monster_FrameMove(float fSpeed);

public:
	void Set_QuestAccess() { m_bIsQuestAccess = false; }

public:
	void Initialize();

public:
	static CGameObject* Create();

private:
	bool					m_bIsQuestAccess;
};

#endif // !__HARRYCAIN_H__

