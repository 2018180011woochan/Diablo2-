#include "stdafx.h"
#include "MonsterAttack.h"
#include "GameObject_Manager.h"

CMonsterAttack::CMonsterAttack()
{
}


CMonsterAttack::~CMonsterAttack()
{
	Release_GameObject();
}

HRESULT CMonsterAttack::Ready_GameObject()
{
	return S_OK;
}

int CMonsterAttack::Update_GameObject()
{
	m_tBullet.vPos += m_tBullet.vDir * m_tBullet.fSpeed * CTime_Manager::Get_Instance()->Get_TimeDelta();
	m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (m_tBullet.eObjState == OBJ_DEATH)
		return OBJ_DEAD;

	if (m_tBullet.vPos.x > m_vecNecromancerPos.x + (WINCX >> 1) || m_tBullet.vPos.x < m_vecNecromancerPos.x - (WINCX >> 1)
		|| m_tBullet.vPos.y > m_vecNecromancerPos.y + (WINCY >> 1) || m_tBullet.vPos.y < m_vecNecromancerPos.y - (WINCY >> 1))
		return OBJ_DEAD;

	FrameMove(0.7f);

	Update_Monster_Bullet_Rect();
	return OBJ_NOEVENT;
}

void CMonsterAttack::Late_Update_GameObject()
{
}

void CMonsterAttack::Render_GameObject()
{
}

void CMonsterAttack::Release_GameObject()
{
}

CGameObject * CMonsterAttack::Create(BULLET & _tBullet, _vec3 _MonsterPos, float _fAttack)
{
	CGameObject* pInstance = new CMonsterAttack;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CMonsterAttack*>(pInstance)->Initialize(_tBullet, _MonsterPos, _fAttack);
	return pInstance;
}

void CMonsterAttack::Initialize(BULLET & _tBullet, _vec3 _MonsterPos, float _fAttack)
{
	m_tBullet = _tBullet;
	m_tBullet.vPos = _MonsterPos;
	m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	m_tBullet.tFrame = { 0.f, 6.f };
	m_tBullet.fSpeed = 1000.f;
	m_tBullet.vSize = { 1.f, 1.f, 0.f };
	m_tBullet.fAttack = _fAttack;

	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;

	m_tBullet.vDir = m_vecNecromancerPos - m_tBullet.vPos;
	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
}
