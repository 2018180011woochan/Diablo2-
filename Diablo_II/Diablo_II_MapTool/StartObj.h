#pragma once

#ifndef __STARTOBJ_H__
#define __STARTOBJ_H__

class CDiablo_II_MapToolView;
class CStartObj
{
public:
	CStartObj();
	~CStartObj();

public:
	void Set_View(CDiablo_II_MapToolView* pView) { m_pView = pView; }

public:
	HRESULT Ready_Object();
	void Render_Object();
	//void Mini_Render_Object();
	void Release();

public:
	vector<OBJECT*> Get_Object() { return m_vecObject; }
	void Set_Object(vector<OBJECT*> _vecMapObj) { m_vecObject = _vecMapObj; }
public:
	void Obj_Insert(const _vec3& vPos, const BYTE& byDrawID);
	void Delete_Obj();

private:
	vector<OBJECT*> m_vecObject;
	CDiablo_II_MapToolView* m_pView;
};

#endif // !__STARTOBJ_H__

