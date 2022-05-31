#include "stdafx.h"
#include "GameObject.h"
#include "Wraith.h"
#include "SK2.h"
#include "GameObject_Manager.h"

CGameObject::CGameObject()
	: m_fAngle(0.f), m_bIsReward(false), m_iPoisonDmg(0), m_iPoisonMaxDmg(150), m_pGameObject_Manager(CGameObject_Manager::Get_Instance()),
	m_iColdDmg(0), m_iColdMaxDmg(100)
{
	ZeroMemory(&m_tInfo, sizeof(UNITINFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tMonster, sizeof(MONSTER));
	m_ObjDir = OBJDIR_END;
	m_ObjState = OBJSTATE_END;
}


CGameObject::~CGameObject()
{
}

void CGameObject::FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		m_tFrame.fStartFrame = 0.f;
}

void CGameObject::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - 20.f);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - 20.f);
	m_tRect.right = (LONG)(m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) + 20.f);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) + 20.f);
}

void CGameObject::Update_Player_Bullet_Rect()
{
	//m_tRect.left = (LONG)(m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - 20.f);
	//m_tRect.top = (LONG)(m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - 20.f);
	//m_tRect.right = (LONG)(m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) + 20.f);
	//m_tRect.bottom = (LONG)(m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) + 20.f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
}

void CGameObject::Update_Monster_Bullet_Rect()
{
	m_tRect.left = (LONG)(m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - 20.f);
	m_tRect.top = (LONG)(m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - 20.f);
	m_tRect.right = (LONG)(m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) + 20.f);
	m_tRect.bottom = (LONG)(m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) + 20.f);
}

void CGameObject::Update_Monster_Rect()
{
	//m_tRect.left = (LONG)(m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - 20.f);
	//m_tRect.top = (LONG)(m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - 20.f);
	//m_tRect.right = (LONG)(m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) + 20.f);
	//m_tRect.bottom = (LONG)(m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) + 20.f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_tRect.left = m_tMonster.vPos.x - 20.f;
	m_tRect.top = m_tMonster.vPos.y - 20.f;
	m_tRect.right = m_tMonster.vPos.x + 20.f;
	m_tRect.bottom = m_tMonster.vPos.y + 20.f;
}

void CGameObject::Update_PlayerMonster_Rect()
{
	m_tRect.left = m_tPlayerMonster.vPos.x - 20.f;
	m_tRect.top = m_tPlayerMonster.vPos.y - 20.f;
	m_tRect.right = m_tPlayerMonster.vPos.x + 20.f;
	m_tRect.bottom = m_tPlayerMonster.vPos.y + 20.f;
}

void CGameObject::Update_Diablo_Rect()
{
	m_tRect.left = m_tMonster.vPos.x - 40.f;
	m_tRect.top = m_tMonster.vPos.y - 40.f;
	m_tRect.right = m_tMonster.vPos.x + 40.f;
	m_tRect.bottom = m_tMonster.vPos.y + 40.f;
}

void CGameObject::Update_Rect_NoScroll()
{

	m_tRect.left = (LONG)(m_tInfo.vPos.x - 20.f);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - 20.f);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + 20.f);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + 20.f);
}

//HRESULT CGameObject::Load_Monster(const wstring & wstrFilePath)
//{
//	
//}
