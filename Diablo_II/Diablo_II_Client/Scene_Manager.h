#pragma once

#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"
class CScene_Manager final
{
	DECLARE_SINGLETON(CScene_Manager)
public:
	CScene_Manager();
	virtual ~CScene_Manager();

public:
	HRESULT Scene_Change_SceneManager(SCENEID eNextSceneID);
public:
	int		Update_SceneManager();
	void	Late_Update_SceneManager();
	void	Render_SceneManager();
	void	Release_SceneManager();
public:
	SCENEID m_eCurrentScene;
	SCENEID m_eNextScene;
	CScene* m_pCurrentScene;
};

#endif // !__SCENEMANAGER_H__

