#pragma once

#ifndef __TILE_H__
#define __TILE_H__

#include "GameObject.h"
class CTile final : public CGameObject
{
private:
	explicit CTile();
public:
	virtual ~CTile();

public:
	HRESULT LoadTile(const wstring& wstrFilePath);

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
	vector<TILE*> m_vecTile;
};

#endif // !__TILE_H__

