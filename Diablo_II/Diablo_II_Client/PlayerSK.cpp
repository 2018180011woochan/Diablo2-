#include "stdafx.h"
#include "PlayerSK.h"
#include "GameObject_Manager.h"
#include "PlayerSummonAttack.h"

CPlayerSK::CPlayerSK()
	: m_pDiablo(nullptr)
{
}


CPlayerSK::~CPlayerSK()
{
	Release_GameObject();
}

void CPlayerSK::Move(_vec3 _vecTarget)
{
	if (!(m_tPlayerMonster.eObjState == OBJ_DEATH))
	{
		if (!(m_tPlayerMonster.eObjState == OBJ_ATTACK))
		{
			m_tPlayerMonster.eObjState = OBJ_WALK;

			// 플레이어보다 몬스터가 왼쪽에 있음
			if (_vecTarget.x/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ > m_tPlayerMonster.vPos.x)
			{
				m_tPlayerMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (_vecTarget.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_RIGHT_BOTTOM;

					m_tPlayerMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(_vecTarget.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tPlayerMonster.vPos.x) < 50.f)
					{
						m_tPlayerMonster.eObjDir = OBJ_BOTTOM;
						m_tPlayerMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (_vecTarget.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_RIGHT_TOP;

					m_tPlayerMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(_vecTarget.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tPlayerMonster.vPos.x) < 50.f)
					{
						m_tPlayerMonster.eObjDir = OBJ_TOP;
						m_tPlayerMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(_vecTarget.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tPlayerMonster.vPos.y) < 50.f)
				{
					m_tPlayerMonster.eObjDir = OBJ_RIGHT;
					m_tPlayerMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 플레이어보다 몬스터가 오른쪽에 있음
			if (_vecTarget.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ < m_tPlayerMonster.vPos.x)
			{
				m_tPlayerMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (_vecTarget.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_LEFT_BOTTOM;

					m_tPlayerMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (_vecTarget.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_LEFT_TOP;

					m_tPlayerMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(_vecTarget.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tPlayerMonster.vPos.y) < 50.f)
				{
					m_tPlayerMonster.eObjDir = OBJ_LEFT;
					m_tPlayerMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
		}
	}

}

void CPlayerSK::ToDiabloMove()
{
	if (!(m_tPlayerMonster.eObjState == OBJ_DEATH))
	{
		if (!(m_tPlayerMonster.eObjState == OBJ_ATTACK))
		{
			m_tPlayerMonster.eObjState = OBJ_WALK;

			// 플레이어보다 몬스터가 왼쪽에 있음
			if (vecTargetPos.x/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ > m_tPlayerMonster.vPos.x)
			{
				m_tPlayerMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_RIGHT_BOTTOM;

					m_tPlayerMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(vecTargetPos.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tPlayerMonster.vPos.x) < 50.f)
					{
						m_tPlayerMonster.eObjDir = OBJ_BOTTOM;
						m_tPlayerMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_RIGHT_TOP;

					m_tPlayerMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

					// 플레이어랑 몬스터 y좌표가 비슷함
					if (abs(vecTargetPos.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ - m_tPlayerMonster.vPos.x) < 50.f)
					{
						m_tPlayerMonster.eObjDir = OBJ_TOP;
						m_tPlayerMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
					}
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tPlayerMonster.vPos.y) < 50.f)
				{
					m_tPlayerMonster.eObjDir = OBJ_RIGHT;
					m_tPlayerMonster.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 플레이어보다 몬스터가 오른쪽에 있음
			if (vecTargetPos.x /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)*/ < m_tPlayerMonster.vPos.x)
			{
				m_tPlayerMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 플레이어보다 몬스터가 아래쪽에 있음
				if (vecTargetPos.y /*+ CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ > m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_LEFT_BOTTOM;

					m_tPlayerMonster.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어보다 몬스터가 위쪽에 있음
				if (vecTargetPos.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ < m_tPlayerMonster.vPos.y)
				{
					m_tPlayerMonster.eObjDir = OBJ_LEFT_TOP;

					m_tPlayerMonster.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
				}
				// 플레이어랑 몬스터 x좌표가 비슷함
				if (abs(vecTargetPos.y/* + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)*/ - m_tPlayerMonster.vPos.y) < 50.f)
				{
					m_tPlayerMonster.eObjDir = OBJ_LEFT;
					m_tPlayerMonster.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
		}
	}
}

void CPlayerSK::Monster_FrameMove(float fSpeed)
{
	CGameObject* pSkill = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	if (!m_tPlayerMonster.bisDead)
	{
		if (m_tPlayerMonster.eObjState == OBJ_ATTACK)
		{
			m_tPlayerMonster.tFrame.fStartFrame += m_tPlayerMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

			if (m_tPlayerMonster.tFrame.fStartFrame < 7.8f && m_tPlayerMonster.tFrame.fStartFrame > 7.f)
			{
				pSkill = CPlayerSummonAttack::Create(pBullet, m_tPlayerMonster.vPos, m_tPlayerMonster.fAttack);
				if (nullptr != pSkill)
					m_pGameObject_Manager->Set_GameObject(OBJ_SUMMONATTACK, pSkill);
			}

			if (m_tPlayerMonster.tFrame.fStartFrame > m_tPlayerMonster.tFrame.fEndFrame)
				m_tPlayerMonster.tFrame.fStartFrame = 0.f;
		}

		else
		{
			m_tPlayerMonster.tFrame.fStartFrame += m_tPlayerMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
			if (m_tPlayerMonster.tFrame.fStartFrame > m_tPlayerMonster.tFrame.fEndFrame)
				m_tPlayerMonster.tFrame.fStartFrame = 0.f;
		}
	}
}

void CPlayerSK::Monster_DeadFrameMove(float fSpeed)
{
	if (m_tPlayerMonster.bisDead)
	{
		m_tPlayerMonster.tFrame.fStartFrame += m_tPlayerMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tPlayerMonster.tFrame.fStartFrame > m_tPlayerMonster.tFrame.fEndFrame)
			m_tPlayerMonster.tFrame.fStartFrame = 18.f;
	}
}

void CPlayerSK::Monster_CreateFrameMove(float fSpeed)
{
	if (m_tPlayerMonster.eObjState == OBJ_CREATE)
	{
		m_tPlayerMonster.tFrame.fStartFrame += m_tPlayerMonster.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
		if (m_tPlayerMonster.tFrame.fStartFrame > m_tPlayerMonster.tFrame.fEndFrame)
			m_tPlayerMonster.eObjState = OBJ_STAND;
	}
}

HRESULT CPlayerSK::Ready_GameObject()
{
	return S_OK;
}

int CPlayerSK::Update_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	_vec3 NecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float fWidth = abs(NecromancerPos.x - m_tPlayerMonster.vPos.x);
	float fHeight = abs(NecromancerPos.y - m_tPlayerMonster.vPos.y);
	m_tPlayerMonster.fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	if (m_tPlayerMonster.fDistance >= 600.f)
		m_tPlayerMonster.vPos = NecromancerPos;

	m_pDiablo = CGameObject_Manager::Get_Instance()->Get_Diablo();
	vecTargetPos = CGameObject_Manager::Get_Instance()->Get_DiabloPos();

	float fTargetWidth = abs(vecTargetPos.x - m_tPlayerMonster.vPos.x);
	float fTargetHeight = abs(vecTargetPos.y - m_tPlayerMonster.vPos.y);
	m_tPlayerMonster.fTargetDistance = sqrt((fTargetWidth * fTargetWidth) + (fTargetHeight * fTargetHeight));

	if (m_tPlayerMonster.fHP <= 0.f)
	{
		m_tPlayerMonster.eObjState = OBJ_DEATH;
		m_tPlayerMonster.bisDead = true;
	}

	else if (m_tPlayerMonster.fTargetDistance >= 500.f)
	{
		m_tPlayerMonster.eObjState = OBJ_STAND;
	}

	else if (m_tPlayerMonster.fTargetDistance < 500.f && m_tPlayerMonster.fTargetDistance >= 100)
	{
		m_tPlayerMonster.eObjState = OBJ_WALK;
		ToDiabloMove();

	}

	else if (m_tPlayerMonster.fTargetDistance < 100.f)
	{
		m_tPlayerMonster.eObjState = OBJ_ATTACK;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////// 몬스터를 따라가게 할려면 어떻게 해야할까!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?//////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//fCurDistance = 600.f;

	//_m_listMonster = CGameObject_Manager::Get_Instance()->Get_Mosnter();

	//for (auto& iter = _m_listMonster.begin(); iter != _m_listMonster.end(); ++iter)
	//{
	//	//float fPreWidth = abs((*iter)->Get_MonsterPos().x - m_tPlayerMonster.vPos.x);
	//	//float fPreHeight = abs((*iter)->Get_MonsterPos().y - m_tPlayerMonster.vPos.y);
	//	//float fPreDistance = sqrt((fPreWidth * fPreWidth) + (fPreHeight * fPreHeight));
	//	//float fCurDistance = 0.f;

	//	//if (fCurDistance < fPreDistance)
	//	//	fCurDistance = fPreDistance;
	//	//else

	//	vecTargetPos = (*iter)->Get_MonsterPos();

	//	float fWidth = abs(vecTargetPos.x - m_tPlayerMonster.vPos.x);
	//	float fHeight = abs(vecTargetPos.y - m_tPlayerMonster.vPos.y);
	//	m_tPlayerMonster.fTargetDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	//	if (m_tPlayerMonster.fTargetDistance > fCurDistance)
	//	{
	//		continue;
	//	}

	//	//m_tPlayerMonster.fTargetDistance = fCurDistance;

	//	if (m_tPlayerMonster.fTargetDistance >= 500.f)
	//	{
	//		m_tPlayerMonster.eObjState = OBJ_STAND;
	//	}

	//	if (m_tPlayerMonster.fTargetDistance < 500.f && m_tPlayerMonster.fTargetDistance >= 100.f)
	//	{
	//		m_tPlayerMonster.eObjState = OBJ_WALK;
	//		Move(vecTargetPos);
	//	}

	//	if (m_tPlayerMonster.fTargetDistance < 100.f)
	//	{
	//		m_tPlayerMonster.eObjState = OBJ_ATTACK;
	//	}
	//}


	Update_PlayerMonster_Rect();
	return OBJ_NOEVENT;
}

void CPlayerSK::Late_Update_GameObject()
{
	Monster_CreateFrameMove(1.f);
	Monster_DeadFrameMove(1.f);
	Monster_FrameMove(1.f);
}

void CPlayerSK::Render_GameObject()
{
	// 태어날때
	if (m_tPlayerMonster.eObjState == OBJ_CREATE)
	{
		m_tPlayerMonster.tFrame.fEndFrame = 12.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Create_0", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;

		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		if (m_tPlayerMonster.bisPoison)
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
	if (m_tPlayerMonster.eObjState == OBJ_STAND)
	{
		m_tPlayerMonster.tFrame.fEndFrame = 8.f;
		// 12시
		if (m_tPlayerMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_0", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_2", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 3시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_4", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 5시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_6", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 6시
		if (m_tPlayerMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_8", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 8시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_10", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 9시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_12", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 10시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Netural_14", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}

	}

	// 걸을떄
	if (m_tPlayerMonster.eObjState == OBJ_WALK)
	{
		m_tPlayerMonster.tFrame.fEndFrame = 8.f;
		// 12시
		if (m_tPlayerMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_0", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 1시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_2", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 3시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_4", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 5시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_6", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 6시
		if (m_tPlayerMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_8", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 8시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_10", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 9시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_12", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 10시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"walk_14", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}

	//  공격할떄
	if (m_tPlayerMonster.eObjState == OBJ_ATTACK)
	{
		m_tPlayerMonster.tFrame.fEndFrame = 16.f;
		// 12시
		if (m_tPlayerMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_0", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 1시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_2", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 3시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_4", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 5시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_6", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 6시
		if (m_tPlayerMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_8", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 8시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_10", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 9시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_12", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
		// 10시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Attack_14", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}

	// 맞을떄
	if (m_tPlayerMonster.eObjState == OBJ_HIT)
	{
		m_tPlayerMonster.tFrame.fEndFrame = 4.f;
		// 12시
		if (m_tPlayerMonster.eObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_0", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_2", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_4", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_tPlayerMonster.eObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_6", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_tPlayerMonster.eObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_8", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_10", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_12", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_tPlayerMonster.eObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"GetHit_14", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tPlayerMonster.bisPoison)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 255, 100));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	// 주글때
	if (m_tPlayerMonster.eObjState == OBJ_DEATH)
	{
		m_tPlayerMonster.tFrame.fEndFrame = 19.f;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"SK", L"Death_0", DWORD(m_tPlayerMonster.tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;

		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		_matrix matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_tPlayerMonster.vSize.x, m_tPlayerMonster.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tPlayerMonster.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tPlayerMonster.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		matWorld = matScale * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CPlayerSK::Release_GameObject()
{
}

void CPlayerSK::Initialize(_vec3 MonsterPos)
{
	m_tPlayerMonster.vPos = MonsterPos;
	m_tPlayerMonster.eObjState = OBJ_CREATE;
	m_tPlayerMonster.eObjDir = OBJ_BOTTOM;
	m_tPlayerMonster.bisAttack = false;
	m_tPlayerMonster.fAttack = 20.f;
	m_tPlayerMonster.fHP = 50.f;
	m_tPlayerMonster.bisDead = false;
	m_tPlayerMonster.tFrame = { 0.f, 8.f };
	m_tPlayerMonster.vSize = { 1.f, 1.f ,0.f };
	m_tPlayerMonster.iEXP = 400;
	m_tPlayerMonster.bisPoison = false;

	m_tRect.top = m_tPlayerMonster.vPos.y - 20.f;
	m_tRect.left = m_tPlayerMonster.vPos.x - 20.f;
	m_tRect.bottom = m_tPlayerMonster.vPos.y + 20.f;
	m_tRect.right = m_tPlayerMonster.vPos.x + 20.f;

	// 귀찮아서 걍 여기다함
	m_tInfo.fSpeed = 20.f;
}

CGameObject * CPlayerSK::Create( _vec3 MonsterPos)
{
	CGameObject* pInstance = new CPlayerSK;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}

	dynamic_cast<CPlayerSK*>(pInstance)->Initialize(MonsterPos);
	return pInstance;
}
