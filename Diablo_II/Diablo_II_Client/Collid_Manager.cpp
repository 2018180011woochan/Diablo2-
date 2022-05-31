#include "stdafx.h"
#include "Collid_Manager.h"
#include "GameObject.h"
#include "Wraith.h"
#include "SK2.h"
#include "SK.h"
#include "Necromancer.h"
#include "Demon.h"
#include "Diablo.h"
#include "BoneSpear.h"
#include "SK2SkillEffect.h"
#include "SK2_Skill.h"
#include "GameObject_Manager.h"
#include "PlayerSK.h"

CCollid_Manager::CCollid_Manager()
{
}


CCollid_Manager::~CCollid_Manager()
{
}

// Dst -> SK2스킬		Src -> 플레이어
bool CCollid_Manager::isCollision_Rect_SK2Attack_To_Player(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	EFFECT pEffect;
	ZeroMemory(&pEffect, sizeof(EFFECT));
	CGameObject* pSK2Effect;
	CGameObject_Manager*	m_pGameObject_Manager;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				Dst->Bullet_Set_Dead();
				Src->Player_Set_Cold();
				// 이펙트 생성
				pSK2Effect = CSK2SkillEffect::Create(pEffect, dynamic_cast<SK2_Skill*>(Dst)->Get_SK2BulletPos());
				if (nullptr != pSK2Effect)
					m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_EFFECT, pSK2Effect);
				return true;
			}
		}
	}
}

bool CCollid_Manager::isCollision_Rect_MonsterAttack_To_Player(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	CGameObject_Manager*	m_pGameObject_Manager;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				Dst->Bullet_Set_Dead();
				Src->Set_PlayerHP(Dst->Get_MonsterAttackDmg());
				return true;
			}
		}
	}
}

// Dst->플레이어스킬, Src->몬스터
bool CCollid_Manager::isCollision_Rect_MonsterAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				if (!Src->Get_MonsterDead())
				{
					Src->Mosnter_Set_Hit();
					Src->Hit_MonsterDamage(Dst->Get_BulletDamage());
					return true;
				}
			}

		}
	}
}

bool CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				if (!Src->Get_MonsterDead())
				{
					Src->Mosnter_Set_Hit();
					Src->Hit_MonsterDamage(Dst->Get_BulletDamage());
					Src->Monster_Set_Poison();
					return true;
				}
			}

		}
	}
}

bool CCollid_Manager::isCollision_Rect_PoisonNovaAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				if (!Src->Get_MonsterDead())
				{
					Dst->Bullet_Set_Dead();
					Src->Mosnter_Set_Hit();
					Src->Monster_Set_Poison();
					Src->Hit_MonsterDamage(Dst->Get_BulletDamage());
					return true;
				}
			}

		}
	}
}

bool CCollid_Manager::isCollision_Rect_DeadMonsterAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				if (Src->Get_MonsterDead())
				{
					Src->Mosnter_Set_Hit();
					Src->Hit_MonsterDamage(Dst->Get_BulletDamage());
					return true;
				}
			}

		}
	}
}

bool CCollid_Manager::isCollision_Rect_MonsterAttack_No_Hit_Motion(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				if (!Src->Get_MonsterDead())
				{
					Src->Hit_MonsterDamage(Dst->Get_BulletDamage());
					return true;
				}
			}

		}
	}
}

bool CCollid_Manager::isCollision_Rect_SummonAttackToDiablo(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				if (!Src->Get_MonsterDead())
				{
					Dst->Bullet_Set_Dead();
					Src->Mosnter_Set_Hit();
					Src->Hit_MonsterDamage(Dst->Get_BulletDamage());
					return true;
				}
			}

		}
	}
}

bool CCollid_Manager::isCollision_Rect_DiabloAttackToPlayer(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	CGameObject_Manager*	m_pGameObject_Manager;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				Src->Set_PlayerHP(1000);
				Src->Hit_PlayerMonsterDamage(1000);
				return true;
			}
		}
	}
}
