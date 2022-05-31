#pragma once

#ifndef __GAMEOBJECTMANAGER_H__
#define __GAMEOBJECTMANAGER_H__

class CGameObject;
class CGameObject_Manager
{
	DECLARE_SINGLETON(CGameObject_Manager)

public:
	CGameObject_Manager();
	~CGameObject_Manager();

public:
	CGameObject* Get_Terrain() { return m_listObject[OBJ_TERRAIN].front(); }
	CGameObject* Get_Player() { return m_listObject[OBJ_PLAYER].front(); }
	CGameObject* Get_HarryCain() { return m_listObject[OBJ_HARRYCAIN].front(); }
	CGameObject* Get_Portal() { return m_listObject[OBJ_POTAL].front(); }
	CGameObject* Get_Diablo() { return m_listObject[OBJ_DIABLO].front(); }

	list<CGameObject*> Get_Mosnter() { return m_listObject[OBJ_MONSTER]; }

public:
	_vec3 Get_NecromancerPos();
	_vec3 Get_DiabloPos();

public:
	HRESULT Add_GameObject_Manager(OBJID eID, CGameObject* pObject);
	void	Update_GameObject_Manager();
	void	Late_Update_GameObject_Manager();
	void	Render_GameObject_Manager();
	void	Release_GameObject_Manager();

public:
	void Combat_Wraith_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	void Combat_SK_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	void Combat_SK2_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	void Combat_Demon_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);

public:
	void Set_GameObject(OBJID _eObjID, CGameObject* _pGameObject) { m_listObject[_eObjID].emplace_back(_pGameObject); }

public:
	HRESULT LoadMonster(const wstring& _wstrPath);

private:
	list<CGameObject*>		m_listObject[OBJ_END];

};

#endif // !__GAMEOBJECTMANAGER_H__

