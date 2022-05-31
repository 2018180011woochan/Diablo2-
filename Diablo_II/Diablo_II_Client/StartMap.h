#pragma once

#ifndef __STARTMAP_H__
#define __STARTMAP_H__

#include "Scene.h"

class CGameObject_Manager;
class CGameObject;
class CStartTile;
class CStartMapObj;
class CHarryCain;
class CStartMap final : public CScene
{
private:
	explicit CStartMap();
public:
	virtual ~CStartMap();

public:
	virtual HRESULT Ready_Scene();
	virtual int		Update_Scene();
	virtual void	Late_Update_Scene();
	virtual void	Render_Scene();
	virtual void	Release_Scene();

public:
	static CScene* Create();


private:
	CGameObject_Manager*	m_pGameObject_Manager;

	CGameObject*			pHarryCain;
	CGameObject*			pPlayer;
	UNITINFO*				m_UnitInfo;
	CGameObject* pTile;
	CGameObject* pMapObj;
	CGameObject* pPotal;
	CGameObject*			pQuestWnd;

	RECT rHarryCainRect;
	RECT rMouseRect;
	RECT rPortalRect;
	bool					m_bisPotal;
};

#endif // !__STARTMAP_H__

