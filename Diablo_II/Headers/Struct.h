#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "Enum.h"

typedef struct tagTexturePath
{
	wstring wstrRelativePath = L"";
	wstring wstrObjectKey = L"";
	wstring wstrStateKey = L"";
	DWORD	dwCount = 0;
}TEXPATH;

typedef struct tagTexInfo
{
	// 이미지 한장을 제어하기 위한 컴객체. 예쩐에 쓰던 HBITMAP과 동일한 역할을 수행할 것. 
	LPDIRECT3DTEXTURE9 pTexture; 

	// 이미지에 대한 정보를 담고 있을 구조체. 
	D3DXIMAGE_INFO tImageInfo; 
}TEXINFO;

typedef struct tagTile
{
	_vec3 vPos; 
	_vec3 vSize; 
	//int		iIndex;
	//int		iParentIndex;
	BYTE byDrawID; 
	BYTE byOption; 
}TILE;

typedef struct tagObject
{
	_vec3 vPos;
	_vec3 vSize;
	BYTE byDrawID;
}OBJECT;



typedef struct tagUI
{
	_vec3 vPos;
	_vec3 vSize;
}UI;

typedef struct tagFrame
{
	float fStartFrame;
	float fEndFrame;
}FRAME;

typedef struct tagMonster
{
	_vec3		vPos;
	_vec3		vSize;
	BYTE		byMonsterID;

	OBJSTATE	eObjState;
	OBJDIR		eObjDir;
	float		fDistance;

	bool		bisAttack;
	bool		bisDead;
	bool		bisCreate;
	bool		bisBurrow;
	bool		bisPoison;

	float		fAttack;
	float		fHP;
	
	int			iEXP;

	RECT		tRect;
	FRAME		tFrame;

}MONSTER;

typedef struct tagPlayerMonster
{
	_vec3		vPos;
	_vec3		vSize;
	BYTE		byMonsterID;

	OBJSTATE	eObjState;
	OBJDIR		eObjDir;
	float		fDistance;
	float		fTargetDistance;

	bool		bisAttack;
	bool		bisDead;
	bool		bisCreate;
	bool		bisBurrow;
	bool		bisPoison;

	float		fAttack;
	float		fHP;

	int			iEXP;

	RECT		tRect;
	FRAME		tFrame;

}PLAYERMONSTER;

typedef struct tagBullet
{
	_vec3		vPos;
	_vec3		vSize;
	_vec3		vDir;

	FRAME		tFrame;
	float		fAttack;
	float		fBulletImageDir;
	float		fSpeed;
	OBJSTATE	eObjState;
	bool		bIsDead;

	RECT		tRect;
}BULLET;

typedef struct tagEffect
{
	_vec3		vPos;
	_vec3		vSize;
	FRAME		tFrame;
	RECT		tRect;
	float		fSpeed;

	bool		bisDead;
}EFFECT;

typedef struct tagNecromancerSkillPoint
{
	int Teeth;
	int BoneArmor;
	int PoisonDagger;
	int CorpseExplosion;
	int BornWall;
	int PoisonExplosion;
	int BoneSpear;
	int BonePrison;
	int PoisonNova;
	int BornSpirit;
}POISONANDBORNSKILLPOINT;

typedef struct tagNecromancerSummonSkillPoint
{
	int SkeletonMastery;
	int RaiseSkeleton;
	int CrayGolem;
	int GolemMastery;
	int RaiseSkeletonMage;
	int BloodGolem;
	int SummonResist;
	int IronGolem;
	int FireGolem;
	int Revive;
}SUMMONSKILLPOINT;

typedef struct tagNecromancerSummonSkillCheck
{
	bool SkeletonMastery;
	bool RaiseSkeleton;
	bool CrayGolem;
	bool GolemMastery;
	bool RaiseSkeletonMage;
	bool BloodGolem;
	bool SummonResist;
	bool IronGolem;
	bool FireGolem;
	bool Revive;
}SUMMONSKILLCHECK;

typedef struct tagNecromancerSkillIsCheck
{
	bool Teeth;
	bool BoneArmor;
	bool PoisonDagger;
	bool CorpseExplosion;
	bool BornWall;
	bool PoisonExplosion;
	bool BoneSpear;
	bool BonePrison;
	bool PoisonNova;
	bool BornSpirit;
}NECROMANCERSKILLCHECK;

typedef struct tagUnitInfo
{
#ifdef _AFX
	CString wstrName;
	CString wstrJob;
#else
	wstring wstrName;
	wstring wstrJob;
#endif // AFX
	//int iAtt; 
	//int iDef; 
	//BYTE byJop;
	//BYTE byItem; 
	
	_vec3 vPos;
	_vec3 vSize;
	_vec3 vDir;

	float fSpeed;
	float fRunSpeed;
	bool  bIsCold;

	// 상단
	int iLevel;
	int iEXP;
	int iNextLevel;
	int iStamina;
	int iMaxStamina;

	// 왼쪽
	float fStrength;				// 힘
	float fDexterity;				// 민첩
	float fVitality;				// 생명력
	float fEnergy;					// 에너지
	float fPoint;					// 남은 스탯포인트
	
	int iSkillPoint;				// 스킬포인트
	POISONANDBORNSKILLPOINT tSkillPoint;
	NECROMANCERSKILLCHECK	tSkillCheck;

	SUMMONSKILLPOINT		tSummonSkillPoint;
	SUMMONSKILLCHECK		tSummonSkillCheck;
	// 오른쪽
	float		fAttackDamage;			// 공격력
	float		fDefence;				// 회피
	float		fStamina;				// 스태미나
	float		fHP;					// 체력
	float		fMaxHP;
	float		fMP;
	float		fMaxMP;
	// 마나

}UNITINFO;

#endif // !__STRUCT_H__


