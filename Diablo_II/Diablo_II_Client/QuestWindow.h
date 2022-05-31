#pragma once

#ifndef __QUESTWINDOW_H__
#define __QUESTWINDOW_H__

#include "GameObject.h"
class CQuestWindow final : public CGameObject
{
private:
	explicit CQuestWindow();
public:
	virtual ~CQuestWindow();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void Set_DiabloDead() { m_bisDiabloDead = true; }

public:
	void QuestFrameMove(float fSpeed);

public:
	static CGameObject* Create();

private:
	bool m_bisDiabloDead;
};

#endif // !__QUESTWINDOW_H__

