#pragma once

#ifndef __MAINAPP_H__
#define __MAINAPP_H__

class CGameObject_Manager;
class CScene_Manager;
class CFrame_Manager;
class CKey_Manager;
class CScroll_Manager;
class CMainApp final
{
private:
	explicit CMainApp();
public:
	virtual ~CMainApp() = default;

public:
	HRESULT Ready_MainApp();
	void Update_MainApp();
	void LateUpdate_MainApp();
	void Render_MainApp(CFrame_Manager* pFrameManager);
	void Release_MainApp();

public:
	static CMainApp* Create();
	void Free();

private:
	CGraphic_Device*		 m_pGraphic_Device;
	CGameObject_Manager*	 m_pGameObject_Manager;
	CScene_Manager*			 m_pScene_Manager;
	CKey_Manager*			 m_pKey_Manager;
	CScroll_Manager*		 m_pScroll_Manager;

	FRAME					 m_tFrame;
};

#endif // !__MAINAPP_H__

