#pragma once

#ifndef __KEYMANAGER_H__
#define __KEYMANAGER_H__

class CKey_Manager
{
	DECLARE_SINGLETON(CKey_Manager)

public:
	CKey_Manager();
	~CKey_Manager();

public:
	void Key_Update();
	bool Key_Up(DWORD dwKey);
	bool Key_Down(DWORD dwKey);
	bool Key_Pressing(DWORD dwKey);

private:
	DWORD m_dwKey;
	DWORD m_dwKeyDown;
	DWORD m_dwKeyUp;
};

#endif // !__KEYMANAGER_H__

