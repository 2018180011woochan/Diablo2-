#pragma once

#ifndef __STARTMAPOBJ_H__
#define __STARTMAPOBJ_H__

#include "GameObject.h"
class CStartMapObj final : public CGameObject
{
private:
	explicit CStartMapObj();
public:
	virtual ~CStartMapObj();

public:
	HRESULT Load_StartMapObject(const wstring & wstrFilePath);

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();
private:
	vector<OBJECT*> m_vecStartMapObject;
};

#endif // !__STARTMAPOBJ_H__

