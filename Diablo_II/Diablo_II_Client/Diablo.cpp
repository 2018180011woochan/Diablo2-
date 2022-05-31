#include "stdafx.h"
#include "Diablo.h"
#include "GameObject_Manager.h"
#include "Necromancer.h"
#include "MonsterAttack.h"
#include "FireSpread.h"
#include "Breath.h"
#include "GroundFire.h"
#include "SoundMgr.h"

CDiablo::CDiablo()
	: m_dwSkillTime(0.f), m_eCurrentObjstate(OBJSTATE_END), m_bisDiabloDead(true)
{
}


CDiablo::~CDiablo()
{
	Release_GameObject();
}

void CDiablo::Move()
{
	_vec3 pt = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (!(m_tMonster.eObjState == OBJ_DEATH))
	{
		if (!((m_tMonster.eObjState == OBJ_ATTACK) || (m_tMonster.eObjState == OBJ_FIRESPREAD) || (m_tMonster.eObjState == OBJ_GROUNDFIRE) || (m_tMonster.eObjState == OBJ_BREATH)))
		{
			m_tMonster.eObjState = OBJ_WALK;

			// 플레이어보다 몬스터가 왼쪽에 있음
			if (pt.x/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ > m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(pt.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_BOTTOM;
						m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(pt.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_TOP;
						m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_RIGHT;
					m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 플레이어보다 몬스터가 오른쪽에 있음
			if (pt.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ < m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (pt.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(pt.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_LEFT;
					m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
		}
	}
}

void CDiablo::Run()
{
	_vec3 pt = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (!(m_tMonster.eObjState == OBJ_DEATH))
	{
		if (!((m_tMonster.eObjState == OBJ_ATTACK) || (m_tMonster.eObjState == OBJ_FIRESPREAD) || (m_tMonster.eObjState == OBJ_GROUNDFIRE) || (m_tMonster.eObjState == OBJ_BREATH)))
		{
			m_tMonster.eObjState = OBJ_DASH;

			// 플레이어보다 몬스터가 왼쪽에 있음
			if (pt.x/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ > m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed * 2.f);

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed * 2.f);

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(pt.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_BOTTOM;
						m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * ((m_tInfo.fSpeed * 2.f) / 5);
					}
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed * 2.f);

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(pt.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_TOP;
						m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * ((m_tInfo.fSpeed * 2.f) / 5);
					}
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_RIGHT;
					m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * ((m_tInfo.fSpeed * 2.f) / 5);
				}
			}
			// 플레이어보다 몬스터가 오른쪽에 있음
			if (pt.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ < m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed * 2.f);

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (pt.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed * 2.f);
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (pt.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed * 2.f);
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(pt.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_LEFT;
					m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * ((m_tInfo.fSpeed * 2.f) / 5);
				}
			}
		}
	}
}

void CDiablo::Skill()
{
	if (m_eCurrentObjstate == OBJ_FIRESPREAD)
	{
		m_tMonster.eObjState = OBJ_BREATH;
		m_eCurrentObjstate = OBJ_BREATH;
		return;
	}

	if (m_eCurrentObjstate == OBJ_BREATH)
	{
		m_tMonster.eObjState = OBJ_GROUNDFIRE;
		m_eCurrentObjstate = OBJ_GROUNDFIRE;
		return;
	}

	if (m_tMonster.eObjState != OBJ_FIRESPREAD)
	{
		m_tMonster.eObjState = OBJ_FIRESPREAD;
		m_eCurrentObjstate = OBJ_FIRESPREAD;
	}

	
}

void CDiablo::Monster_FrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (!m_tMonster.bisDead)
	{
		if (m_tMonster.eObjState == OBJ_ATTACK)
		{
			m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

			if (m_tMonster.tFrame.fStartFrame < 9.8f && m_tMonster.tFrame.fStartFrame > 9.f)
			{
				pSkill = CMonsterAttack::Create(pBullet, m_tMonster.vPos, m_tMonster.fAttack);
				if (nullptr != pSkill)
					m_pGameObject_Manager->Set_GameObject(OBJ_MONSTERATTACK, pSkill);
			}

			if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
				m_tMonster.tFrame.fStartFrame = 0.f;
		}

		else
		{
			m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
			if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
				m_tMonster.tFrame.fStartFrame = 0.f;
		}
	}
}

void CDiablo::Monster_FireSpreadFrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (m_tMonster.eObjState == OBJ_FIRESPREAD)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > 16 && m_tMonster.tFrame.fStartFrame < 16.8)
			m_tMonster.eObjState = OBJ_STAND;

		if (m_tMonster.tFrame.fStartFrame > 10 && m_tMonster.tFrame.fStartFrame < 10.8)
		{
			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			///////////////////////////////////////////////////////

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			///////////////////////////////////////////////////////////////

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 5, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y - 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y + 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x + 5, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			/////////////////////////////////////////////////////////////////////

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 5, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y + 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y - 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CFireSpread::Create(pBullet, _vec3(m_tMonster.vPos.x - 5, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);
		}
	}
}

void CDiablo::Monster_DeadFrameMove(float fSpeed)
{
	if (m_tMonster.bisDead)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
		{
			m_tMonster.tFrame.fStartFrame = 141.f;
			//m_bisDiabloDead = true;
		}
	}
}

void CDiablo::Monster_BreathFrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (m_tMonster.eObjState == OBJ_BREATH)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > 16 && m_tMonster.tFrame.fStartFrame < 16.8)
			m_tMonster.eObjState = OBJ_STAND;

		if (m_tMonster.tFrame.fStartFrame > 2 && m_tMonster.tFrame.fStartFrame <= 16)
		{
			//fSpeed = 0.01f;
			pSkill = CBreath::Create(pBullet, m_tMonster.vPos);
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);
		}
	}
}

void CDiablo::Monster_GroundFireFrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (m_tMonster.eObjState == OBJ_GROUNDFIRE)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > 14 && m_tMonster.tFrame.fStartFrame < 14.8)
			m_tMonster.eObjState = OBJ_STAND;

		if (m_tMonster.tFrame.fStartFrame > 4 && m_tMonster.tFrame.fStartFrame <= 14)
		{

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x + 10, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

			pSkill = CGroundFire::Create(pBullet, _vec3(m_tMonster.vPos.x - 10, m_tMonster.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_DIABLOATTACK, pSkill);

		}
	}
}

HRESULT CDiablo::Ready_GameObject()
{
	return S_OK;
}

int CDiablo::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	_vec3 NecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float fWidth = abs(NecromancerPos.x - m_tMonster.vPos.x);
	float fHeight = abs(NecromancerPos.y - m_tMonster.vPos.y);
	m_tMonster.fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	m_dwSkillTime += CTime_Manager::Get_Instance()->Get_TimeDelta();

	if (m_tMonster.eObjState != OBJ_DEATH)
	{
		if (m_dwSkillTime >= 5.f)
		{
			Skill();
			CSoundMgr::Get_Instance()->PlaySound(L"DiabloAttack.wav", CSoundMgr::DIABLOATTACK);
			//m_tMonster.eObjState = OBJ_FIRESPREAD;
			m_tMonster.tFrame.fStartFrame = 0.f;
			m_dwSkillTime = 0.f;
			bisDiabloDead = true;
		}
	}

	if (!((m_tMonster.eObjState == OBJ_FIRESPREAD) || (m_tMonster.eObjState == OBJ_GROUNDFIRE) || (m_tMonster.eObjState == OBJ_BREATH)))
	{

		if (m_tMonster.fHP <= 0.f)
		{
			if (!m_bIsReward)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"DiabloDead.wav", CSoundMgr::DIABLODEAD);
				m_pPlayer->Set_PlayerEXP(Get_MonsterExp());
				m_bIsReward = true;
			}
			m_tMonster.eObjState = OBJ_DEATH;
			m_tMonster.bisDead = true;
		}

		else if (m_tMonster.fDistance >= 800.f)
		{
			m_tMonster.eObjState = OBJ_STAND;
		}

		else if (m_tMonster.fDistance < 800.f && m_tMonster.fDistance >= 500.f)
		{
			m_tMonster.eObjState = OBJ_WALK;
			Move();
		}

		else if (m_tMonster.fDistance < 500.f && m_tMonster.fDistance >= 200.f)
		{
			m_tMonster.eObjState = OBJ_DASH;
			Run();
		}
		else if (m_tMonster.fDistance < 200.f)
		{
			m_tMonster.eObjState = OBJ_ATTACK;
		}

		if (m_tMonster.bisPoison)
		{
			if (m_iPoisonMaxDmg > m_iPoisonDmg)
			{
				m_tMonster.fHP -= 1;
				m_iPoisonDmg++;
			}
			else
			{
				m_iPoisonDmg = 0;
				m_tMonster.bisPoison = false;
			}
		}
	}
	Update_Diablo_Rect();
	return OBJ_NOEVENT;
}

void CDiablo::Late_Update_GameObject()
{
	Monster_FrameMove(0.7f);
	Monster_DeadFrameMove(0.1f);
	Monster_FireSpreadFrameMove(0.1f);
	Monster_BreathFrameMove(0.01f);
	Monster_GroundFireFrameMove(0.1f);
}

void CDiablo::Render_GameObject()
{
	// 그라운드파이어
	if (m_tMonster.eObjState == OBJ_GROUNDFIRE)
	{
		m_tMonster.tFrame.fEndFrame = 16.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"SpecialCast_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 브레스
	if (m_tMonster.eObjState == OBJ_BREATH)
	{
		m_tMonster.tFrame.fEndFrame = 17.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Special_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 파이어캐스트
	if (m_tMonster.eObjState == OBJ_FIRESPREAD)
	{
		m_tMonster.tFrame.fEndFrame = 18.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"FireCast_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 뛸때
	if (m_tMonster.eObjState == OBJ_DASH)
	{
		m_tMonster.tFrame.fEndFrame = 22.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Run_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 서있을때
	if (m_tMonster.eObjState == OBJ_STAND)
	{
		m_tMonster.tFrame.fEndFrame = 12.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Netural_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 걸을떄
	if (m_tMonster.eObjState == OBJ_WALK)
	{
		m_tMonster.tFrame.fEndFrame = 12.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Walk_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	//  공격할떄
	if (m_tMonster.eObjState == OBJ_ATTACK)
	{
		m_tMonster.tFrame.fEndFrame = 16.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Attack_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}


	// 맞을떄
	if (m_tMonster.eObjState == OBJ_HIT)
	{
		m_tMonster.tFrame.fEndFrame = 6.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_8", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_10", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_12", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"GetHit_14", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 주글때
	if (m_tMonster.eObjState == OBJ_DEATH)
	{
		m_tMonster.tFrame.fEndFrame = 142.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Diablo", L"Death_0", DWORD(m_tMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;

		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CDiablo::Release_GameObject()
{
}

void CDiablo::Initialize(MONSTER & _tMonster)
{
	m_tMonster = _tMonster;
	m_tMonster.eObjState = OBJ_STAND;
	m_tMonster.eObjDir = OBJ_BOTTOM;
	m_tMonster.bisAttack = false;
	m_tMonster.fAttack = 200.f;
	m_tMonster.fHP = 150000.f;
	//m_tMonster.fHP = 1500.f;
	m_tMonster.bisDead = false;
	m_tMonster.tFrame = { 0.f, 15.f };
	m_tMonster.vSize = { 1.5f,1.5f,0.f };
	m_tMonster.iEXP = 10000;
	m_tMonster.bisPoison = false;

	m_tRect.top = m_tMonster.vPos.y - 40.f;
	m_tRect.left = m_tMonster.vPos.x - 40.f;
	m_tRect.bottom = m_tMonster.vPos.y + 40.f;
	m_tRect.right = m_tMonster.vPos.x + 40.f;

	// 귀찮아서 걍 여기다함
	m_tInfo.fSpeed = 40.f;
}

CGameObject * CDiablo::Create(MONSTER & _tMonster)
{
	CGameObject* pInstance = new CDiablo;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CDiablo*>(pInstance)->Initialize(_tMonster);
	return pInstance;
}


