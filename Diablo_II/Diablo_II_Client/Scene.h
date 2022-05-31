#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

class CScene
{
protected:
	explicit CScene();
public:
	virtual ~CScene();

public:
	virtual HRESULT Ready_Scene()			PURE;
	virtual int		Update_Scene()			PURE;
	virtual void	Late_Update_Scene()		PURE;
	virtual void	Render_Scene()			PURE;
	virtual void	Release_Scene()			PURE;
};

#endif // !__SCENE_H__

