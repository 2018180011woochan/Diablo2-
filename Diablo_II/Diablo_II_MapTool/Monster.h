#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

class CDiablo_II_MapToolView;
class CMonster
{
public:
	CMonster();
	~CMonster();

public:
	void Set_View(CDiablo_II_MapToolView* pView) { m_pView = pView; }

public:
	HRESULT Ready_Object();
	void Render_Object();
	void Release();

public:
	vector<MONSTER*> Get_Object() { return m_vecMonster; }
	void Set_Object(vector<MONSTER*> _vecMonster) { m_vecMonster = _vecMonster; }
public:
	void Obj_Insert(const _vec3& vPos, const BYTE& byDrawID);
	void Delete_Obj();

private:
	vector<MONSTER*> m_vecMonster;
	CDiablo_II_MapToolView* m_pView;
};

#endif // !__MONSTER_H__

