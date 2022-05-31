#include "stdafx.h"
#include "Demon.h"
#include "GameObject_Manager.h"
#include "MonsterAttack.h"
#include "SoundMgr.h"

CDemon::CDemon()
{
}


CDemon::~CDemon()
{
	Release_GameObject();
}

void CDemon::Move()
{
	_vec3 pt = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (!(m_tMonster.eObjState == OBJ_DEATH))
	{
		if (!(m_tMonster.eObjState == OBJ_ATTACK))
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

void CDemon::Monster_FrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (!m_tMonster.bisDead)
	{
		if (m_tMonster.eObjState == OBJ_ATTACK)
		{
			m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

			if (m_tMonster.tFrame.fStartFrame < 11.8f && m_tMonster.tFrame.fStartFrame > 11.f)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"IzualAttack.wav", CSoundMgr::MONSTERATTACK);
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

void CDemon::Monster_DeadFrameMove(float fSpeed)
{
	if (m_tMonster.bisDead)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
			m_tMonster.tFrame.fStartFrame = 19.f;
	}
}

HRESULT CDemon::Ready_GameObject()
{
	return S_OK;
}

int CDemon::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	_vec3 NecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float fWidth = abs(NecromancerPos.x - m_tMonster.vPos.x);
	float fHeight = abs(NecromancerPos.y - m_tMonster.vPos.y);
	m_tMonster.fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	if (m_tMonster.fHP <= 0.f)
	{
		if (!m_bIsReward)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"AndarielInit.wav", CSoundMgr::MONSTERDEAD);
			m_pPlayer->Set_PlayerEXP(Get_MonsterExp());
			m_bIsReward = true;
		}
		m_tMonster.eObjState = OBJ_DEATH;
		m_tMonster.bisDead = true;
	}

	else if (m_tMonster.fDistance >= 400.f)
	{
		m_tMonster.eObjState = OBJ_STAND;
	}

	else if (m_tMonster.fDistance < 400.f && m_tMonster.fDistance >= 100.f)
	{
		m_tMonster.eObjState = OBJ_WALK;
		Move();
	}
	else if (m_tMonster.fDistance < 100.f)
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

	Update_Monster_Rect();
	return OBJ_NOEVENT;
}

void CDemon::Late_Update_GameObject()
{
	Monster_DeadFrameMove(1.f);
	Monster_FrameMove(1.f);
}

void CDemon::Render_GameObject()
{
	// 서있을때
	if (m_tMonster.eObjState == OBJ_STAND)
	{
		m_tMonster.tFrame.fEndFrame = 8.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_8", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_10", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_12", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Neutral_14", DWORD(m_tMonster.tFrame.fStartFrame));
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
		m_tMonster.tFrame.fEndFrame = 8.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_8", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_10", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_12", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"walk_14", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_8", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_10", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_12", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Attack_14", DWORD(m_tMonster.tFrame.fStartFrame));
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
		m_tMonster.tFrame.fEndFrame = 5.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_8", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_10", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_12", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"GetHit_14", DWORD(m_tMonster.tFrame.fStartFrame));
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
		m_tMonster.tFrame.fEndFrame = 20.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Demon", L"Death_0", DWORD(m_tMonster.tFrame.fStartFrame));
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

void CDemon::Release_GameObject()
{
}

void CDemon::Initialize(MONSTER & _tMonster)
{
	m_tMonster = _tMonster;
	m_tMonster.eObjState = OBJ_STAND;
	m_tMonster.eObjDir = OBJ_BOTTOM;
	m_tMonster.bisAttack = false;
	m_tMonster.fAttack = 20.f;
	m_tMonster.fHP = 3000.f;
	m_tMonster.bisDead = false;
	m_tMonster.tFrame = { 0.f, 8.f };
	m_tMonster.vSize = { 1.f,1.f,1.f };
	m_tMonster.iEXP = 1000;
	m_tMonster.bisPoison = false;

	m_tRect.top = m_tMonster.vPos.y - 20.f;
	m_tRect.left = m_tMonster.vPos.x - 20.f;
	m_tRect.bottom = m_tMonster.vPos.y + 20.f;
	m_tRect.right = m_tMonster.vPos.x + 20.f;

	// 귀찮아서 걍 여기다함
	m_tInfo.fSpeed = 20.f;
}

CGameObject * CDemon::Create(MONSTER& _tMonster)
{
	CGameObject* pInstance = new CDemon;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CDemon*>(pInstance)->Initialize(_tMonster);
	return pInstance;
}
