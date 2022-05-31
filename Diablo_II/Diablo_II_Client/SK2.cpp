#include "stdafx.h"
#include "SK2.h"
#include "GameObject_Manager.h"
#include "SK2_Skill.h"
#include "SoundMgr.h"

CSK2::CSK2()
	: m_pGameObject_Manager(nullptr)
{
}

CSK2::~CSK2()
{
}

void CSK2::Move()
{
	_vec3 pt = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	
	if (!(m_tMonster.eObjState == OBJ_DEATH))
	{
		if (!(m_tMonster.eObjState == OBJ_ATTACK))
		{
			m_tMonster.eObjState = OBJ_WALK;

			// 플레이어보다 몬스터가 왼쪽에 있음
			if (pt.x > m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (pt.y > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(pt.x - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_BOTTOM;
						m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (pt.y < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(pt.x - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_TOP;
						m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(pt.y - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_RIGHT;
					m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 플레이어보다 몬스터가 오른쪽에 있음
			if (pt.x < m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (pt.y > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (pt.y < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(pt.y - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_LEFT;
					m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
		}
	}
}

void CSK2::Attack()
{
}

HRESULT CSK2::Ready_GameObject()
{
	return S_OK;
}


int CSK2::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	_vec3 NecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float fWidth = abs(NecromancerPos.x - m_tMonster.vPos.x);
	float fHeight = abs(NecromancerPos.y - m_tMonster.vPos.y);
	m_tMonster.fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	if (m_tMonster.eObjState == OBJ_HIT)
		m_tMonster.eObjState = OBJ_STAND;

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

	else if (m_tMonster.fDistance >= 500.f)
	{
		if (m_tMonster.bisBurrow)
		{
			m_tMonster.eObjState = OBJ_BURROW;
		}
		else
			m_tMonster.eObjState = OBJ_STAND;
	}

	else if (m_tMonster.fDistance < 500.f && m_tMonster.fDistance >= 400)
	{
		m_tMonster.bisBurrow = false;
		if (!m_tMonster.bisCreate)
		{
			m_tMonster.bisCreate = true;
			m_tMonster.eObjState = OBJ_CREATE;
		}
		else
		{
			m_tMonster.eObjState = OBJ_WALK;
			Move();
		}
	}

	else if (m_tMonster.fDistance < 400.f && m_tMonster.fDistance >= 300.f)
	{
		m_tMonster.eObjState = OBJ_WALK;
		Move();
	}

	else if (m_tMonster.fDistance < 300.f)
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

void CSK2::Monster_FrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (!m_tMonster.bisDead)
	{
		if (m_tMonster.eObjState == OBJ_ATTACK)
		{
			m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

			if (m_tMonster.tFrame.fStartFrame < 8.8f && m_tMonster.tFrame.fStartFrame > 8.f)
			{
				pSkill = SK2_Skill::Create(pBullet, m_tMonster.vPos);
				CSoundMgr::Get_Instance()->PlaySound(L"FingerMageAttack.wav", CSoundMgr::SK2ATTACK);
				if (nullptr != pSkill)
					m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_SK2ATTACK, pSkill);
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

void CSK2::Monster_DeadFrameMove(float fSpeed)
{
	if (m_tMonster.bisDead)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
			m_tMonster.tFrame.fStartFrame = 18.f;
	}
}

void CSK2::Late_Update_GameObject()
{
	Monster_DeadFrameMove(1.f);
	Monster_FrameMove(1.f);
}

void CSK2::Render_GameObject()
{
	if (m_tMonster.eObjState == OBJ_BURROW)
	{ }

	// 태어날때
	if (m_tMonster.eObjState == OBJ_CREATE)
	{
		m_tMonster.tFrame.fEndFrame = 12.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Create_0", DWORD(m_tMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;

		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		if (m_tMonster.bisPoison)
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
		else
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}


	// 서있을때
	if (m_tMonster.eObjState == OBJ_STAND)
	{
		m_tMonster.tFrame.fEndFrame = 8.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_3", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_5", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_7", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_1", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"stand_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}

	}

	// 걸을떄
	if (m_tMonster.eObjState == OBJ_WALK)
	{
		m_tMonster.tFrame.fEndFrame = 8.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_5", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_7", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_1", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"walk_3", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
	}

	//  공격할떄
	if (m_tMonster.eObjState == OBJ_ATTACK)
	{
		m_tMonster.tFrame.fEndFrame = 16.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_4", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 1시
		if (m_tMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_5", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 3시
		if (m_tMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_6", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 5시
		if (m_tMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_7", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 6시
		if (m_tMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_0", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 8시
		if (m_tMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_1", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 9시
		if (m_tMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_2", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		// 10시
		if (m_tMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Attack_3", DWORD(m_tMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
	}

	// 주글때
	if (m_tMonster.eObjState == OBJ_DEATH)
	{
		m_tMonster.tFrame.fEndFrame = 19.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK2", L"Death_0", DWORD(m_tMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;

		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}
}

void CSK2::Release_GameObject()
{
}

void CSK2::Initialize(MONSTER & _tMonster)
{
	m_tMonster = _tMonster;
	m_tMonster.eObjState = OBJ_BURROW;
	m_tMonster.eObjDir = OBJ_BOTTOM;
	m_tMonster.bisAttack = false;
	m_tMonster.fAttack = 200.f;
	m_tMonster.fHP = 3000.f;
	m_tMonster.bisDead = false;
	m_tMonster.tFrame = { 0.f, 12.f };
	m_tMonster.vSize = { 1.5f, 1.5f, 0.f };
	m_tMonster.bisCreate = false;
	m_tMonster.bisBurrow = true;
	m_tMonster.bisPoison = false;
	m_tMonster.iEXP = 500;

	m_tRect.top = m_tMonster.vPos.y - 20.f;
	m_tRect.left = m_tMonster.vPos.x - 20.f;
	m_tRect.bottom = m_tMonster.vPos.y + 20.f;
	m_tRect.right = m_tMonster.vPos.x + 20.f;

	// 귀찮아서 걍 여기다함
	m_tInfo.fSpeed = 15.f;
}

CGameObject * CSK2::Create(MONSTER& _tMonster)
{
	CGameObject* pInstance = new CSK2;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CSK2*>(pInstance)->Initialize(_tMonster);
	return pInstance;
}
