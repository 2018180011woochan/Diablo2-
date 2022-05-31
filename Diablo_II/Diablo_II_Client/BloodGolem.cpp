#include "stdafx.h"
#include "BloodGolem.h"
#include "GameObject_Manager.h"
#include "PlayerSummonAttack.h"

CBloodGolem::CBloodGolem()
	: m_pDiablo(nullptr)
{
}


CBloodGolem::~CBloodGolem()
{
	Release_GameObject();
}

void CBloodGolem::ToDiabloMove()
{
	if (!(m_tMonster.eObjState == OBJ_DEATH))
	{
		if (!(m_tMonster.eObjState == OBJ_ATTACK))
		{
			m_tMonster.eObjState = OBJ_WALK;

			// 플레이어보다 몬스터가 왼쪽에 있음
			if (vecTargetPos.x/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ > m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(vecTargetPos.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_BOTTOM;
						m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_RIGHT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(vecTargetPos.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tMonster.vPos.x) < 50.f)
					{
						m_tMonster.eObjDir = OBJ_TOP;
						m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_RIGHT;
					m_tMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 플레이어보다 몬스터가 오른쪽에 있음
			if (vecTargetPos.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ < m_tMonster.vPos.x)
			{
				m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_BOTTOM;

					m_tMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (vecTargetPos.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tMonster.vPos.y)
				{
					m_tMonster.eObjDir = OBJ_LEFT_TOP;

					m_tMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(vecTargetPos.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tMonster.vPos.y) < 50.f)
				{
					m_tMonster.eObjDir = OBJ_LEFT;
					m_tMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
		}
	}
}

void CBloodGolem::Monster_FrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (!m_tMonster.bisDead)
	{
		if (m_tMonster.eObjState == OBJ_ATTACK)
		{
			m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

			if (m_tMonster.tFrame.fStartFrame < 7.8f && m_tMonster.tFrame.fStartFrame > 7.f)
			{
				pSkill = CPlayerSummonAttack::Create(pBullet, m_tMonster.vPos, m_tMonster.fAttack);
				if (nullptr != pSkill)
					m_pGameObject_Manager->Set_GameObject(OBJ_SUMMONATTACK, pSkill);
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

void CBloodGolem::Monster_DeadFrameMove(float fSpeed)
{
	if (m_tMonster.bisDead)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
			m_tMonster.tFrame.fStartFrame = 14.f;
	}
}

void CBloodGolem::Monster_CreateFrameMove(float fSpeed)
{
	if (m_tMonster.eObjState == OBJ_CREATE)
	{
		m_tMonster.tFrame.fStartFrame += m_tMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tMonster.tFrame.fStartFrame > m_tMonster.tFrame.fEndFrame)
			m_tMonster.eObjState = OBJ_STAND;
	}
}

HRESULT CBloodGolem::Ready_GameObject()
{
	return S_OK;
}

int CBloodGolem::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	_vec3 NecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float fWidth = abs(NecromancerPos.x - m_tMonster.vPos.x);
	float fHeight = abs(NecromancerPos.y - m_tMonster.vPos.y);
	m_tMonster.fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	if (m_tMonster.fDistance >= 600.f)
		m_tMonster.vPos = NecromancerPos;

	m_pDiablo = CGameObject_Manager::Get_Instance()->Get_Diablo();
	vecTargetPos = CGameObject_Manager::Get_Instance()->Get_DiabloPos();

	float fTargetWidth = abs(vecTargetPos.x - m_tMonster.vPos.x);
	float fTargetHeight = abs(vecTargetPos.y - m_tMonster.vPos.y);
	m_tMonster.fTargetDistance = sqrt((fTargetWidth * fTargetWidth) + (fTargetHeight * fTargetHeight));

	if (m_tMonster.fHP <= 0.f)
	{
		m_tMonster.eObjState = OBJ_DEATH;
		m_tMonster.bisDead = true;
	}

	else if (m_tMonster.fTargetDistance >= 500.f)
	{
		m_tMonster.eObjState = OBJ_STAND;
	}

	else if (m_tMonster.fTargetDistance < 500.f && m_tMonster.fTargetDistance >= 100)
	{
		m_tMonster.eObjState = OBJ_WALK;
		ToDiabloMove();

	}

	else if (m_tMonster.fTargetDistance < 100.f)
	{
		m_tMonster.eObjState = OBJ_ATTACK;
	}

	Update_Monster_Rect();
	return OBJ_NOEVENT;
}

void CBloodGolem::Late_Update_GameObject()
{
	Monster_CreateFrameMove(1.f);
	Monster_DeadFrameMove(1.f);
	Monster_FrameMove(1.f);
}

void CBloodGolem::Render_GameObject()
{
	// 태어날때
	if (m_tMonster.eObjState == OBJ_CREATE)
	{
		m_tMonster.tFrame.fEndFrame = 16.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Create_0", DWORD(m_tMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;

		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tMonster.vSize.x, m_tMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		if (m_tMonster.bisPoison)
		{
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
		else
		{
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			CGraphic_Device::Get_Instance()->Get_Sprite()->End();
			CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
	}


	// 서있을때
	if (m_tMonster.eObjState == OBJ_STAND)
	{
		m_tMonster.tFrame.fEndFrame = 4.f;
		// 12시
		if (m_tMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_5", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_7", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_1", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"stand_3", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_5", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_7", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_1", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"walk_3", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_4", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_5", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_6", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_7", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_0", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_1", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_2", DWORD(m_tMonster.tFrame.fStartFrame));
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
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Attack_3", DWORD(m_tMonster.tFrame.fStartFrame));
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
		m_tMonster.tFrame.fEndFrame = 16.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Golem_blood", L"Dead_0", DWORD(m_tMonster.tFrame.fStartFrame));
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

void CBloodGolem::Release_GameObject()
{
}

void CBloodGolem::Initialize(_vec3 MonsterPos)
{
	m_tMonster.vPos = MonsterPos;
	m_tMonster.eObjState = OBJ_CREATE;
	m_tMonster.eObjDir = OBJ_BOTTOM;
	m_tMonster.bisAttack = false;
	m_tMonster.fAttack = 20.f;
	m_tMonster.fHP = 5000.f;
	m_tMonster.bisDead = false;
	m_tMonster.tFrame = { 0.f, 4.f };
	m_tMonster.vSize = { 1.5f, 1.5f ,0.f };
	m_tMonster.iEXP = 400;
	m_tMonster.bisPoison = false;

	m_tRect.top = m_tMonster.vPos.y - 20.f;
	m_tRect.left = m_tMonster.vPos.x - 20.f;
	m_tRect.bottom = m_tMonster.vPos.y + 20.f;
	m_tRect.right = m_tMonster.vPos.x + 20.f;

	// 귀찮아서 걍 여기다함
	m_tInfo.fSpeed = 20.f;
}

CGameObject * CBloodGolem::Create(_vec3 MonsterPos)
{
	CGameObject* pInstance = new CBloodGolem;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CBloodGolem*>(pInstance)->Initialize(MonsterPos);
	return pInstance;
}
