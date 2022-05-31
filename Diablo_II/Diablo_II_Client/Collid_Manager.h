#pragma once

#ifndef __COLLIDMANAGER_H__
#define __COLLIDMANAGER_H__

class CGameObject;
class CCollid_Manager
{
public:
	CCollid_Manager();
	~CCollid_Manager();

public:
	// 몬스터가 플레이어 공격
	static bool isCollision_Rect_SK2Attack_To_Player(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_MonsterAttack_To_Player(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);

	// 플레이어가 몬스터 공격
	static bool isCollision_Rect_MonsterAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_PoisonExplosionAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_PoisonNovaAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_DeadMonsterAttack(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_MonsterAttack_No_Hit_Motion(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_SummonAttackToDiablo(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);
	static bool isCollision_Rect_DiabloAttackToPlayer(list<CGameObject*>& _Dst, list<CGameObject*>& _Src);

private:

};

#endif // !__COLLIDMANAGER_H__

