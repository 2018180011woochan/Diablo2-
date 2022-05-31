#pragma once

#ifndef __BONESHIELD_H__
#define __BONESHIELD_H__

#include "GameObject.h"
class CBoneShield final : public CGameObject
{
private:
	explicit CBoneShield();
public:
	virtual ~CBoneShield();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
};

#endif // !__BONESHIELD_H__

