#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CGameObject_Manager;
class CGameObject abstract
{
protected:
	explicit CGameObject();
public:
	virtual ~CGameObject();

public:
	void FrameMove(float fSpeed = 1.f);
	void Update_Rect();
	void Update_Player_Bullet_Rect();
	void Update_Monster_Bullet_Rect();
	void Update_Monster_Rect();
	void Update_PlayerMonster_Rect();
	void Update_Diablo_Rect();
	void Update_Rect_NoScroll();

public:
	_vec3 Get_Pos() { return m_tInfo.vPos; }
	_vec3 Get_MonsterPos() { return m_tMonster.vPos; }
	void Set_Pos(const _vec3& vPos) { m_tInfo.vPos = vPos; }
	const RECT& Get_Rect() const { return m_tRect; }

public:
	void Bullet_Set_Dead() { m_tBullet.eObjState = OBJ_DEATH; }
	void Monster_Set_Dead() { m_tMonster.eObjState = OBJ_DEATH; }
	void Mosnter_Set_Hit() { m_tMonster.eObjState = OBJ_HIT; }
	void Monster_Set_Poison() { m_tMonster.bisPoison = true; }
	void Player_Set_Cold() { m_tInfo.bIsCold = true; }

public:
	float Get_AttackDamage() { return m_tInfo.fAttackDamage; }
	bool Get_MonsterDead() { return m_tMonster.bisDead; }
	float Get_MonsterAttackDmg() { return m_tBullet.fAttack; }
	float Get_BulletDamage() { return m_tBullet.fAttack; }
	int Get_MonsterExp() { return m_tMonster.iEXP; }

public:
	void Hit_MonsterDamage(float _fDamage) { m_tMonster.fHP -= _fDamage; }
	void Hit_PlayerMonsterDamage(float _fDamage) { m_tPlayerMonster.fHP -= _fDamage; }

public:
	void Set_PlayerEXP(int _Exp) { m_tInfo.iEXP += _Exp; }
	void Set_PlayerHP(float _HP) { m_tInfo.fHP -= _HP; }
	

public:
	virtual HRESULT Ready_GameObject()			PURE;
	virtual int		Update_GameObject()			PURE;
	virtual void	Late_Update_GameObject()	PURE;
	virtual void	Render_GameObject()			PURE;
	virtual void	Release_GameObject()		PURE;

public:
	void Set_Dir(float _x, float _y, float _z = 0) { m_tInfo.vDir = { _x, _y, _z }; }
	void Set_Scale(float _fX, float _fY, float _fZ) { m_fScaleX = _fX; m_fScaleY = _fY; m_fScaleZ = _fZ; }
	void Set_ScaleX(float _fScaleX) { m_fScaleX = _fScaleX; }
	void Set_ScaleY(float _fScaleY) { m_fScaleY = _fScaleY; }
	void Set_ScaleZ(float _fScaleZ) { m_fScaleZ = _fScaleZ; }
	void Set_Angle(float _fX, float _fY, float _fZ) { m_fAngleX = _fX; m_fAngleY = _fY, m_fAngleZ = _fZ; }
	void Set_AngleX(float _fAngleX) { m_fAngleX = _fAngleX; }
	void Set_AngleY(float _fAngleY) { m_fAngleY = _fAngleY; }
	void Set_AngleZ(float _fAngleZ) { m_fAngleZ = _fAngleZ; }


	void Update_Vector()
	{
		D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matTrans, matRevRotZ, matParent, matWorld;
		D3DXMatrixScaling(&matScale, m_fScaleX, m_fScaleY, m_fScaleZ);

		D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngleX));
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngleY));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngleZ));

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		D3DXMatrixRotationZ(&matRevRotZ, D3DXToRadian(m_fRevAngleZ));
		D3DXMatrixTranslation(&matParent, m_vParentPos.x, m_vParentPos.y, m_vParentPos.z);
		matWorld = matScale * matRotX * matRotY * matRotZ * matTrans * matRevRotZ * matParent;
	}

protected:
	UNITINFO		m_tInfo;
	MONSTER			m_tMonster;
	BULLET			m_tBullet;
	EFFECT			m_tEffect;
	FRAME			m_tFrame;
	PLAYERMONSTER	m_tPlayerMonster;

	OBJDIR			m_ObjDir;
	OBJSTATE		m_ObjState;
	bool			m_bIsReward;

	RECT			m_tRect;
	CGameObject*	m_pPlayer;
	UNITINFO*		m_pUnitInfo;


	int				m_iPoisonMaxDmg;
	int				m_iPoisonDmg;
	int				m_iColdMaxDmg;
	int				m_iColdDmg;
	CGameObject_Manager* m_pGameObject_Manager;

	float				m_fAngle;
	float				m_fScaleX;		// X축 스케일 크기
	float				m_fScaleY;		// Y축 스케일 크기
	float				m_fScaleZ;		// Z축 스케일 크기
	float				m_fAngleX;		// X 회전 각도
	float				m_fAngleY;		// Y 회전 각도
	float				m_fAngleZ;		// Z 회전 각도
	float				m_fRevAngleZ;	// Z 자전 각도
	_vec3				m_vParentPos;	// 부모와의 거리

};

#endif // !__GAMEOBJECT_H__

