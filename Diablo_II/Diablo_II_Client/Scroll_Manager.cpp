#include "stdafx.h"
#include "Scroll_Manager.h"

_vec3 CScroll_Manager::m_vScroll = {};

CScroll_Manager::CScroll_Manager()
{
}


CScroll_Manager::~CScroll_Manager()
{
}

float CScroll_Manager::Get_Scroll(SCROLL eScrollID)
{


	switch (eScrollID)
	{
	case SCROLL_X:
		return m_vScroll.x;
	case SCROLL_Y:
		return m_vScroll.y;
	}

	return 0.0f;
}

//_vec3 CScroll_Manager::Get_Scroll()
//{
//	return m_vScroll;
//}

void CScroll_Manager::Set_Scroll(const _vec3 & vScroll)
{
	m_vScroll = vScroll;
}

void CScroll_Manager::Scroll_Lock()
{/*
	if (0 < m_vScroll.x)
		m_vScroll.x = 0.f;

	if (WINCX - (TILECX * TILEX) > m_vScroll.x)
		m_vScroll.x = WINCX - (TILECX * TILEX);
*/
	if (m_vScroll.x <= 3)
		m_vScroll.x = 3;

	if (m_vScroll.x >= 4900)
		m_vScroll.x = 4900;

	if (m_vScroll.y >= 1629)
		m_vScroll.y = 1629;

	if (m_vScroll.y <= 4)
		m_vScroll.y = 4;
}


