#pragma once

#ifndef __STARTTILE_H__
#define __STARTTILE_H__

#include "GameObject.h"
class CStartTile final : public CGameObject
{
private:
	explicit CStartTile();
public:
	virtual ~CStartTile();

public:
	HRESULT LoadStartTile(const wstring& wstrFilePath);

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create();
private:
	vector<TILE*> m_vecStartTile;
};

#endif // !__STARTTILE_H__

