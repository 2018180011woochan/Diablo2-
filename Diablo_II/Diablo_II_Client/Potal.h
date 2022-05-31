#pragma once

#ifndef __POTAL_H__
#define __POTAL_H__

#include "GameObject.h"
class CPotal final : public CGameObject
{
private:
	explicit CPotal();
public:
	virtual ~CPotal();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void SetFont() { m_bisFont = true; }

public:
	RECT Get_PortalRect() { return m_tRect; }

public:
	void UpdatePotal(float fSpeed);

public:
	void Initialize();

public:
	static CGameObject* Create();
	
private:
	bool m_bisFont;
};

#endif // !__POTAL_H__
