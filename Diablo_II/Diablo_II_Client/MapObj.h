#pragma once

#ifndef __MAPOBJ_H__
#define __MAPOBJ_H__

#include "GameObject.h"
class CMapObj final : public CGameObject
{
private:
	explicit CMapObj();
public:
	virtual ~CMapObj();

public:
	HRESULT Load_MapObject(const wstring & wstrFilePath);

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();
private:
	vector<OBJECT*> m_vecMapObject;
};

#endif // !__MAPOBJ_H__

