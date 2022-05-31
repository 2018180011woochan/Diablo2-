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
	// �̹��� ������ �����ϱ� ���� �İ�ü. ��¾�� ���� HBITMAP�� ������ ������ ������ ��. 
	LPDIRECT3DTEXTURE9 pTexture; 

	// �̹����� ���� ������ ��� ���� ����ü. 
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

	// ���
	int iLevel;
	int iEXP;
	int iNextLevel;
	int iStamina;
	int iMaxStamina;

	// ����
	float fStrength;				// ��
	float fDexterity;				// ��ø
	float fVitality;				// �����
	float fEnergy;					// ������
	float fPoint;					// ���� ��������Ʈ
	
	int iSkillPoint;				// ��ų����Ʈ
	POISONANDBORNSKILLPOINT tSkillPoint;
	NECROMANCERSKILLCHECK	tSkillCheck;

	SUMMONSKILLPOINT		tSummonSkillPoint;
	SUMMONSKILLCHECK		tSummonSkillCheck;
	// ������
	float		fAttackDamage;			// ���ݷ�
	float		fDefence;				// ȸ��
	float		fStamina;				// ���¹̳�
	float		fHP;					// ü��
	float		fMaxHP;
	float		fMP;
	float		fMaxMP;
	// ����

}UNITINFO;

#endif // !__STRUCT_H__


