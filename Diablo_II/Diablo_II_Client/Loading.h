#pragma once

#ifndef __LOADING_H__
#define __LOADING_H__

#include "Scene.h"
class CLoading final : public CScene
{
public:
	explicit CLoading();
	virtual ~CLoading();

public:
	virtual HRESULT Ready_Scene() override;
	virtual int Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	static unsigned int __stdcall ImageLoadFunc(LPVOID pArgment);

public:
	static CScene* Create();

public:
	void FrameMove(float fSpeed = 1.f);

private:
	CRITICAL_SECTION m_Critical_Section;
	HANDLE m_hThread;

	FRAME m_tFrame;
};

#endif // !__LOADING_H__

