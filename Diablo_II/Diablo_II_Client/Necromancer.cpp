#include "stdafx.h"
#include "Necromancer.h"
#include "Key_Manager.h"
#include "BoneSpear.h"
#include "BoneSpearEffect.h"
#include "GameObject_Manager.h"
#include "AnimationEffect_Implement.h"
#include "NormalEffect.h"
#include "BuffEffect.h"
#include "CorpseExplodeGuts.h"
#include "PoisonNova.h"
#include "PoisonExplosion.h"
#include "PlayerSK.h"
#include "PlayerSK2.h"
#include "FireGolem.h"
#include "BloodGolem.h"
#include "StoneGolem.h"
#include "PlayerSummonAttack.h"
#include "SoundMgr.h"
#include "SoundMgr.h"


CNecromancer::CNecromancer()
	: m_pGameObject_Manager(CGameObject_Manager::Get_Instance()),
	m_eSkill(SKILL_END), m_bisBoneSpearShot(false), m_fDeltaTime(5.f), m_fWidth(0.f), m_fHeight(0.f), m_fDistance(0.f), m_iSkeletonCnt(0), m_bBloodGolem(false), m_bisDiabloInit(false), m_bSoundstop(true),
	fWidth(0.f), fHeight(0.f), fDistance(0.f)
{
}


CNecromancer::~CNecromancer()
{
	Release_GameObject();
}

HRESULT CNecromancer::Ready_GameObject()
{
	//m_tInfo.vPos = { float(WINCX >> 1), float(WINCY >> 1) * 5.f, 0.f };
	//m_tInfo.vSize = { 1.5f, 1.5f, 0.f };
	//m_tFrame = { 0.f, 8.f };
	//m_tInfo.fSpeed = 100.f;
	//m_tInfo.fRunSpeed = 60.f;

	//m_tInfo.fStrength = 25.f;
	//m_tInfo.fDexterity = 25.f;
	//m_tInfo.fVitality = 25.f;
	//m_tInfo.fEnergy = 25.f;
	//m_tInfo.fPoint = 15.f;
	//m_tInfo.iSkillPoint = 100.f;

	//m_tInfo.bIsCold = false;
	//m_tInfo.fMaxHP = 5000.f;
	//m_tInfo.fMaxMP = 1000.f;
	//m_tInfo.fHP = m_tInfo.fMaxHP;
	//m_tInfo.fMP = m_tInfo.fMaxMP;

	//m_tInfo.iLevel = 1;
	//m_tInfo.iNextLevel = 10000;
	//m_tInfo.iMaxStamina = 500;
	//m_tInfo.iStamina = m_tInfo.iMaxStamina;

	//m_tInfo.fAttackDamage = 200.f;
	//m_tInfo.fDefence = 5.f;

	//m_ObjDir = OBJ_BOTTOM;
	//m_ObjState = OBJ_STAND;

	//// 일단 이걸로 확인
	//m_eSkill = SKILL_BONESPEAR;

	//CScroll_Manager::Set_Scroll(_vec3(float(WINCX >> 1), float((WINCY >> 1) * 5.f), 0.f));
	return S_OK;
}

int CNecromancer::Update_GameObject()
{
	CGameObject* pSkill = nullptr;

	if (m_tInfo.fHP <= 0.f)
		m_tInfo.fHP = 0.f;
	if (m_tInfo.fMP <= 0.f)
		m_tInfo.fMP = 0.f;
	if (m_tInfo.iStamina <= 0)
		m_tInfo.iStamina = 0;

	if (m_ObjState != OBJ_DASH)
		m_tInfo.iStamina += 5;

	if (m_tInfo.iStamina >= m_tInfo.iMaxStamina)
		m_tInfo.iStamina = m_tInfo.iMaxStamina;

	if (!bisOpenSkillWnd && !bisOpenStatWnd)
	{
		if (!bisOpenStatWnd)
		{
			Attack_Skill();
			Move();
			Offset();
			Update_Rect();
		}
	}

	if (m_tInfo.bIsCold)
	{
		if (m_iColdMaxDmg > m_iColdDmg)
		{
			m_iColdDmg++;
			m_tInfo.fSpeed = 10.f;
		}
		else
		{
			m_iColdDmg = 0;
			m_tInfo.fSpeed = 100.f;
			m_tInfo.bIsCold = false;
		}
	}

	_vec3 DiaPos = CGameObject_Manager::Get_Instance()->Get_DiabloPos();

	fWidth = abs(DiaPos.x - m_tInfo.vPos.x);
	fHeight = abs(DiaPos.y - m_tInfo.vPos.y);
	fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	if (m_bSoundstop)
	{
		if (fDistance <= 500)
			m_bisDiabloInit = true;
		m_bSoundstop = false;
	}

	if (GetAsyncKeyState('Z'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"DiabloInit.wav", CSoundMgr::DIABLOINIT);
		m_bisDiabloInit = false;
	}

	Level_Up();
	return OBJ_NOEVENT;
}

void CNecromancer::Late_Update_GameObject()
{
	FrameMove(1.f);

	if (!bisOpenSkillWnd && !bisOpenStatWnd)
	{
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Walk.wav", CSoundMgr::WALK);
			m_ObjState = OBJ_WALK;
			if (m_tInfo.iStamina > 0)
			{
				if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_LCONTROL))
				{
					if (m_tInfo.iStamina <= 0)
					{
						m_ObjState = OBJ_WALK;
					}
					m_ObjState = OBJ_DASH;
					m_tInfo.iStamina--;
				}
			}
		}
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_LCONTROL) || CKey_Manager::Get_Instance()->Key_Up(KEY_LBUTTON) || CKey_Manager::Get_Instance()->Key_Up(KEY_RBUTTON))
		{
			m_tFrame = { 0.f, 8.f };
			m_ObjState = OBJ_STAND;
		}
	}
}

void CNecromancer::Render_GameObject()
{
	if (m_ObjState == OBJ_STAND)
	{
		// 12시
		if (m_ObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_0", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_ObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_2", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_ObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_4", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_ObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_6", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_ObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_8", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_ObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_10", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_ObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_12", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_ObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"stand_14", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		
	}

	if (m_ObjState == OBJ_WALK)
	{
		// 12시
		if (m_ObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_0", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_ObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_2", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_ObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_4", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_ObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_6", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_ObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_8", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_ObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_10", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_ObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_12", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_ObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"walk_14", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	if (m_ObjState == OBJ_DASH)
	{
		// 12시
		if (m_ObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_0", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_ObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_2", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_ObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_4", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_ObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_6", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_ObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_8", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_ObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_10", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_ObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_12", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_ObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"dash_14", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	if (m_ObjState == OBJ_SKILLATTACK)
	{
		// 12시
		if (m_ObjDir == OBJ_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_0", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 1시
		if (m_ObjDir == OBJ_RIGHT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_2", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 3시
		if (m_ObjDir == OBJ_RIGHT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_4", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 5시
		if (m_ObjDir == OBJ_RIGHT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_6", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 6시
		if (m_ObjDir == OBJ_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_8", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 8시
		if (m_ObjDir == OBJ_LEFT_BOTTOM)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_10", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 9시
		if (m_ObjDir == OBJ_LEFT)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_12", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 10시
		if (m_ObjDir == OBJ_LEFT_TOP)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"skill_14", DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;

			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			_matrix matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			if (m_tInfo.bIsCold)
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 50, 50, 255));
			else
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

}

void CNecromancer::Release_GameObject()
{
	//CGameObject_Manager::Get_Instance()->Release_GameObject_Manager();
}

void CNecromancer::Move()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	//ClientToScreen(g_hWND, &pt);
	
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// 커서보다 캐릭터가 왼쪽에 있음
		if (pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) > m_tInfo.vPos.x)
		{
			if (m_ObjState == OBJ_DASH)
				m_tInfo.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
			m_tInfo.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

			// 커서보다 캐릭터가 아래쪽에 있음
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) > m_tInfo.vPos.y)
			{
				m_ObjDir = OBJ_RIGHT_BOTTOM;

				if (m_ObjState == OBJ_DASH)
					m_tInfo.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
				m_tInfo.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 커서랑 캐릭터 y좌표가 비슷함
				if (abs(pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - m_tInfo.vPos.x) < 50.f)
				{
					m_ObjDir = OBJ_BOTTOM;
					if (m_ObjState == OBJ_DASH)
						m_tInfo.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
					m_tInfo.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 커서보다 캐릭터가 위쪽에 있음
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) < m_tInfo.vPos.y)
			{
				m_ObjDir = OBJ_RIGHT_TOP;

				if (m_ObjState == OBJ_DASH)
					m_tInfo.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
				m_tInfo.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

				// 커서랑 캐릭터 y좌표가 비슷함
				if (abs(pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - m_tInfo.vPos.x) < 50.f)
				{
					m_ObjDir = OBJ_TOP;
					if (m_ObjState == OBJ_DASH)
						m_tInfo.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
					m_tInfo.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
				}
			}
			// 커서랑 캐릭터 x좌표가 비슷함
			if (abs(pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - m_tInfo.vPos.y) < 50.f)
			{
				m_ObjDir = OBJ_RIGHT;
				if (m_ObjState == OBJ_DASH)
					m_tInfo.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
				m_tInfo.vPos.x += CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
			}
		}
		// 커서보다 캐릭터가 오른쪽에 있음
		if (pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) < m_tInfo.vPos.x)
		{
			if (m_ObjState == OBJ_DASH)
				m_tInfo.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
			m_tInfo.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;

			// 커서보다 캐릭터가 아래쪽에 있음
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) > m_tInfo.vPos.y)
			{
				m_ObjDir = OBJ_LEFT_BOTTOM;

				if (m_ObjState == OBJ_DASH)
					m_tInfo.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
				m_tInfo.vPos.y += CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
			}
			// 커서보다 캐릭터가 위쪽에 있음
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) < m_tInfo.vPos.y)
			{
				m_ObjDir = OBJ_LEFT_TOP;

				if (m_ObjState == OBJ_DASH)
					m_tInfo.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
				m_tInfo.vPos.y -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fSpeed;
			}
			// 커서랑 캐릭터 x좌표가 비슷함
			if (abs(pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - m_tInfo.vPos.y) < 50.f)
			{
				m_ObjDir = OBJ_LEFT;
				if (m_ObjState == OBJ_DASH)
					m_tInfo.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * m_tInfo.fRunSpeed;
				m_tInfo.vPos.x -= CTime_Manager::Get_Instance()->Get_TimeDelta() * (m_tInfo.fSpeed / 5);
			}
		}



	}
}

void CNecromancer::Offset()
{
	CScroll_Manager::Set_Scroll(_vec3(m_tInfo.vPos.x - WINCX / 2, m_tInfo.vPos.y - WINCY / 2, 0.f));


	//int iScrollX = (int)CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X);
	//int iOffSet = WINCX >> 1;

	//_vec3 ScrollLockX = { iOffSet - (m_tInfo.vPos.x - iScrollX), 0.f, 0.f };

	//if (iOffSet > m_tInfo.vPos.x + iScrollX)
	//	CScroll_Manager::Set_Scroll(ScrollLockX);


}

void CNecromancer::Attack_Skill()
{
	CGameObject* pSkill = nullptr;
	CGameObject* pBoneSpear = nullptr;
	BULLET pBullet;
	ZeroMemory(&pBullet, sizeof(BULLET));

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	_vec3 vMouse = { float(pt.x) + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), float(pt.y) + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f };

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_RBUTTON))
	{
		m_tFrame = { 0.f, 19.f };
		m_ObjState = OBJ_SKILLATTACK;
		switch (m_eSkill)
		{
		case SKILL_BONESPEAR:
			m_tInfo.fMP -= 10.f;
			pSkill = CBoneSpear::Create(pBullet);
			if (nullptr != pSkill)
			{
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_BONESPEAR, pSkill);
				
			}
			break;

		case SKILL_CORPSEEXPLODEGUTS:
			m_tInfo.fMP -= 10.f;
			pSkill = CCorpseExplodeGuts::Create(pBullet);
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_CORPSEEXPLODEGUTS, pSkill);

			break;

		case SKILL_POISONNOVA:
			CSoundMgr::Get_Instance()->PlaySound(L"FrozenExplode.wav", CSoundMgr::POISONNOVA);
			m_tInfo.fMP -= 10.f;
			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x, m_tInfo.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x, m_tInfo.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 10, m_tInfo.vPos.y, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 10, m_tInfo.vPos.y, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			///////////////////////////////////////////////////////

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 10, m_tInfo.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 10, m_tInfo.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 10, m_tInfo.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 10, m_tInfo.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			///////////////////////////////////////////////////////////////

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 5, m_tInfo.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 10, m_tInfo.vPos.y - 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 10, m_tInfo.vPos.y + 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x + 5, m_tInfo.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			/////////////////////////////////////////////////////////////////////

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 5, m_tInfo.vPos.y + 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 10, m_tInfo.vPos.y + 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 10, m_tInfo.vPos.y - 5, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			pSkill = CPoisonNova::Create(pBullet, _vec3(m_tInfo.vPos.x - 5, m_tInfo.vPos.y - 10, 0.f));
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONNOVA, pSkill);

			break;

		case SKILL_POISONEXPLOSION:
			m_tInfo.fMP -= 10.f;
			pSkill = CPoisonExplosion::Create(pBullet);
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_POISONEXPLOSION, pSkill);
			break;

		case SKILL_RAISESKELETON:
			CSoundMgr::Get_Instance()->PlaySound(L"InitMonster.wav", CSoundMgr::CREATESK);
			m_iSkeletonCnt++;
			pSkill = CPlayerSK::Create(vMouse);
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_PLAYERSK, pSkill);
			break;
		case SKILL_BLOODGOLEM:
			CSoundMgr::Get_Instance()->PlaySound(L"InitMonster.wav", CSoundMgr::CREATESK);
			m_bBloodGolem = true;
			pSkill = CBloodGolem::Create(vMouse);
			if (nullptr != pSkill)
				m_pGameObject_Manager->Get_Instance()->Set_GameObject(OBJ_BLOODGOLEM, pSkill);
			break;
		}
		if (nullptr == pSkill)
			return;
	}


}

void CNecromancer::Level_Up()
{
	if (m_tInfo.iEXP >= m_tInfo.iNextLevel)
	{
		m_tInfo.iLevel++;
		m_tInfo.fHP = m_tInfo.fMaxHP;
		m_tInfo.fMP = m_tInfo.fMaxMP;
		m_tInfo.iEXP = 0;
		m_tInfo.fPoint += 5.f;
		m_tInfo.iNextLevel += 1000;
	}
}

void CNecromancer::Make_BoneSpearEffect(CGameObject * _pObj)
{
}

void CNecromancer::Initialize(_vec3 _PlayerPos)
{
	m_tInfo.vPos = _PlayerPos;
	m_tInfo.vSize = { 1.5f, 1.5f, 0.f };
	m_tFrame = { 0.f, 8.f };
	m_tInfo.fSpeed = 100.f;
	m_tInfo.fRunSpeed = 60.f;

	m_tInfo.fStrength = 25.f;
	m_tInfo.fDexterity = 25.f;
	m_tInfo.fVitality = 25.f;
	m_tInfo.fEnergy = 25.f;
	m_tInfo.fPoint = 15.f;
	m_tInfo.iSkillPoint = 100.f;

	m_tInfo.bIsCold = false;
	m_tInfo.fMaxHP = 5000.f;
	m_tInfo.fMaxMP = 1000.f;
	m_tInfo.fHP = m_tInfo.fMaxHP;
	m_tInfo.fMP = m_tInfo.fMaxMP;

	m_tInfo.iLevel = 1;
	m_tInfo.iNextLevel = 10000;
	m_tInfo.iMaxStamina = 500;
	m_tInfo.iStamina = m_tInfo.iMaxStamina;

	m_tInfo.fAttackDamage = 200.f;
	m_tInfo.fDefence = 5.f;

	m_ObjDir = OBJ_BOTTOM;
	m_ObjState = OBJ_STAND;

	// 일단 이걸로 확인
	m_eSkill = SKILL_BONESPEAR;

	CScroll_Manager::Set_Scroll(_vec3(float(WINCX >> 1), float((WINCY >> 1) * 5.f), 0.f));
}

CNecromancer * CNecromancer::Create(_vec3 _PlayerPos)
{
	CNecromancer* pInstance = new CNecromancer;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CNecromancer*>(pInstance)->Initialize(_PlayerPos);
	return pInstance;
}
