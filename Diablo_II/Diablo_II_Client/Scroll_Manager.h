#pragma once

#ifndef __SCROLLMANAGER_H__
#define __SCROLLMANAGER_H__

class CScroll_Manager
{
public:
	enum SCROLL { SCROLL_X, SCROLL_Y };

public:
	CScroll_Manager();
	~CScroll_Manager();

public:
	static float Get_Scroll(SCROLL eScrollID);
	//static _vec3 Get_Scroll();
	static void Set_Scroll(const _vec3& vScroll);

	static void ScrollYPlus(float _ScrollY) { m_vScroll.y -= _ScrollY; }

public:
	void Scroll_Lock();

private:
	static _vec3 m_vScroll;
	TCHAR		m_szScroll[64];
};

#endif // !__SCROLLMANAGER_H__

