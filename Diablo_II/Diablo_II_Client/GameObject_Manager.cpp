#include "stdafx.h"
#include "GameObject_Manager.h"
#include "GameObject.h"
#include "Necromancer.h"
#include "Collid_Manager.h"
#include "Wraith.h"
#include "SK2.h"
#include "SK.h"
#include "Demon.h"
#include "Diablo.h"
#include "BoneSpear.h"

IMPLEMENT_SINGLETON(CGameObject_Manager)

CGameObject_Manager::CGameObject_Manager()
{
}


CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager();
}

_vec3 CGameObject_Manager::Get_NecromancerPos()
{
	for (auto& iter = m_listObject[OBJ_PLAYER].begin(); iter != m_listObject[OBJ_PLAYER].end(); ++iter)
	{
		return dynamic_cast<CNecromancer*> (*iter)->Get_NecromancerPos();
	}
}

_vec3 CGameObject_Manager::Get_DiabloPos()
{
	for (auto& iter = m_listObject[OBJ_DIABLO].begin(); iter != m_listObject[OBJ_DIABLO].end(); ++iter)
	{
		return dynamic_cast<CDiablo*> (*iter)->Get_DiabloPos();
	}
}

HRESULT CGameObject_Manager::Add_GameObject_Manager(OBJID eID, CGameObject * pObject)
{
	m_listObject[eID].emplace_back(pObject);
	return S_OK;
}

void CGameObject_Manager::Update_GameObject_Manager()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_listObject[i].begin();
		for (; iter != m_listObject[i].end();)
		{
			int iEvent = (*iter)->Update_GameObject();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listObject[i].erase(iter);
			}
			else
				++iter;
		}
	}

	// 본스피어와 몬스터 충돌
	CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_BONESPEAR], m_listObject[OBJID::OBJ_MONSTER]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_BONESPEAR], m_listObject[OBJID::OBJ_WRAITH]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_BONESPEAR], m_listObject[OBJID::OBJ_SK]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack_No_Hit_Motion(m_listObject[OBJID::OBJ_BONESPEAR], m_listObject[OBJID::OBJ_SK2]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_BONESPEAR], m_listObject[OBJID::OBJ_DEMON]);
	CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_BONESPEAR], m_listObject[OBJID::OBJ_DIABLO]);

	// 시폭과 몬스터 충돌
	CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_CORPSEEXPLODEGUTS], m_listObject[OBJID::OBJ_MONSTER]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_CORPSEEXPLODEGUTS], m_listObject[OBJID::OBJ_WRAITH]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_CORPSEEXPLODEGUTS], m_listObject[OBJID::OBJ_SK]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_CORPSEEXPLODEGUTS], m_listObject[OBJID::OBJ_SK2]);
	//CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_CORPSEEXPLODEGUTS], m_listObject[OBJID::OBJ_DEMON]);
	CCollid_Manager::isCollision_Rect_MonsterAttack(m_listObject[OBJID::OBJ_CORPSEEXPLODEGUTS], m_listObject[OBJID::OBJ_DIABLO]);

	// 포이즌노바와 몬스터 충돌
	CCollid_Manager::isCollision_Rect_PoisonNovaAttack(m_listObject[OBJID::OBJ_POISONNOVA], m_listObject[OBJID::OBJ_MONSTER]);
	//CCollid_Manager::isCollision_Rect_PoisonNovaAttack(m_listObject[OBJID::OBJ_POISONNOVA], m_listObject[OBJID::OBJ_WRAITH]);
	//CCollid_Manager::isCollision_Rect_PoisonNovaAttack(m_listObject[OBJID::OBJ_POISONNOVA], m_listObject[OBJID::OBJ_SK]);
	//CCollid_Manager::isCollision_Rect_PoisonNovaAttack(m_listObject[OBJID::OBJ_POISONNOVA], m_listObject[OBJID::OBJ_SK2]);
	//CCollid_Manager::isCollision_Rect_PoisonNovaAttack(m_listObject[OBJID::OBJ_POISONNOVA], m_listObject[OBJID::OBJ_DEMON]);
	CCollid_Manager::isCollision_Rect_PoisonNovaAttack(m_listObject[OBJID::OBJ_POISONNOVA], m_listObject[OBJID::OBJ_DIABLO]);

	// 포이즌익스플러전과 몬스터 충돌
	CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(m_listObject[OBJID::OBJ_POISONEXPLOSION], m_listObject[OBJID::OBJ_MONSTER]);
	//CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(m_listObject[OBJID::OBJ_POISONEXPLOSION], m_listObject[OBJID::OBJ_WRAITH]);
	//CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(m_listObject[OBJID::OBJ_POISONEXPLOSION], m_listObject[OBJID::OBJ_SK]);
	//CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(m_listObject[OBJID::OBJ_POISONEXPLOSION], m_listObject[OBJID::OBJ_SK2]);
	//CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(m_listObject[OBJID::OBJ_POISONEXPLOSION], m_listObject[OBJID::OBJ_DEMON]);
	CCollid_Manager::isCollision_Rect_PoisonExplosionAttack(m_listObject[OBJID::OBJ_POISONEXPLOSION], m_listObject[OBJID::OBJ_DIABLO]);

	// SK2스킬과 플레이어 충돌
	CCollid_Manager::isCollision_Rect_SK2Attack_To_Player(m_listObject[OBJID::OBJ_SK2ATTACK], m_listObject[OBJID::OBJ_PLAYER]);

	// 몬스터 기본공격과 플레이어 충돌
	CCollid_Manager::isCollision_Rect_MonsterAttack_To_Player(m_listObject[OBJID::OBJ_MONSTERATTACK], m_listObject[OBJID::OBJ_PLAYER]);

	// 플레이어 몬스터 공격과 디아블로 충돌
	CCollid_Manager::isCollision_Rect_SummonAttackToDiablo(m_listObject[OBJID::OBJ_SUMMONATTACK], m_listObject[OBJID::OBJ_DIABLO]);

	// 디아블로 공격과 플레이어와 플레이어딱까리들 충돌
	//CCollid_Manager::isCollision_Rect_DiabloAttackToPlayer(m_listObject[OBJID::OBJ_DIABLOATTACK], m_listObject[OBJID::OBJ_PLAYER]);
	CCollid_Manager::isCollision_Rect_DiabloAttackToPlayer(m_listObject[OBJID::OBJ_DIABLOATTACK], m_listObject[OBJID::OBJ_PLAYERSK]);
	CCollid_Manager::isCollision_Rect_DiabloAttackToPlayer(m_listObject[OBJID::OBJ_DIABLOATTACK], m_listObject[OBJID::OBJ_BLOODGOLEM]);
}

void CGameObject_Manager::Late_Update_GameObject_Manager()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (CGameObject*& pGameObject : m_listObject[i])
		{
			pGameObject->Late_Update_GameObject();
		}
	}
}

void CGameObject_Manager::Render_GameObject_Manager()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (CGameObject*& pGameObject : m_listObject[i])
		{
			pGameObject->Render_GameObject();
		}
	}
}

void CGameObject_Manager::Release_GameObject_Manager()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (CGameObject*& pGameObject : m_listObject[i])
			Safe_Delete(pGameObject);

		m_listObject[i].clear();
	}
}

void CGameObject_Manager::Combat_Wraith_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Src->Get_MonsterDead())
				Dst->Set_PlayerEXP(Src->Get_MonsterExp());
		}
	}
}

void CGameObject_Manager::Combat_SK_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Src->Get_MonsterDead())
				Dst->Set_PlayerEXP(Src->Get_MonsterExp());
		}
	}
}

void CGameObject_Manager::Combat_SK2_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Src->Get_MonsterDead())
				Dst->Set_PlayerEXP(Src->Get_MonsterExp());
		}
	}
}

void CGameObject_Manager::Combat_Demon_Win_Reward(list<CGameObject*>& _Dst, list<CGameObject*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Src->Get_MonsterDead())
				Dst->Set_PlayerEXP(Src->Get_MonsterExp());
		}
	}
}

HRESULT CGameObject_Manager::LoadMonster(const wstring & _wstrPath)
{
	HANDLE hFile = CreateFile(_wstrPath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;


	DWORD dwByte = 0;
	MONSTER tMonster;
	ZeroMemory(&tMonster, sizeof(MONSTER));

	CGameObject* pGameObject = nullptr;
	while (true)
	{
		pGameObject = nullptr;

		ReadFile(hFile, &tMonster, sizeof(MONSTER), &dwByte, nullptr);
		if (0 == dwByte)
		{
			break;
		}

		switch (tMonster.byMonsterID)
		{
		case DIABLOMONSTER_WRAITH:
			pGameObject = CWraith::Create(tMonster);
			if (nullptr != pGameObject)
				m_listObject[OBJID::OBJ_MONSTER].emplace_back(pGameObject);
			break;
		case DIABLOMONSTER_SK2:
			pGameObject = CSK2::Create(tMonster);
			if (nullptr != pGameObject)
				m_listObject[OBJID::OBJ_MONSTER].emplace_back(pGameObject);
			break;
		case DIABLOMONSTER_SK:
			pGameObject = CSK::Create(tMonster);
			if (nullptr != pGameObject)
				m_listObject[OBJID::OBJ_MONSTER].emplace_back(pGameObject);
			break;
		case DIABLOMONSTER_DIABLO:
			pGameObject = CDiablo::Create(tMonster);
			if (nullptr != pGameObject)
				m_listObject[OBJID::OBJ_DIABLO].emplace_back(pGameObject);
			break;
		case DIABLOMONSTER_DEMON:
			pGameObject = CDemon::Create(tMonster);
			if (nullptr != pGameObject)
				m_listObject[OBJID::OBJ_MONSTER].emplace_back(pGameObject);
			break;
		case DIABLOMONSTER_END:
			break;
		default:
			break;
		}

		if (nullptr == pGameObject)
			return E_FAIL;
	}

	
	CloseHandle(hFile);
	return S_OK;
}
