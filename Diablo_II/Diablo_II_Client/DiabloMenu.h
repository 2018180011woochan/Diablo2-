#pragma once

#ifndef __DIABLOMENU_H__
#define __DIABLOMENU_H__

#include "Scene.h"
class CDiabloMenu : public CScene
{
public:
	CDiabloMenu();
	virtual ~CDiabloMenu();

public:
	virtual HRESULT Ready_Scene() override;
	virtual int Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	static CScene* Create();
};

#endif // !__DIABLOMENU_H__

