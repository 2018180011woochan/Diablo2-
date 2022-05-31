#include "stdafx.h"
#include "SkillWindow.h"
#include "Key_Manager.h"
#include "GameObject_Manager.h"
#include "Necromancer.h"

CSkillWindow::CSkillWindow()
	:m_dwSkillWndType(2)
{
}


CSkillWindow::~CSkillWindow()
{
	Release_GameObject();
}

HRESULT CSkillWindow::Ready_GameObject()
{
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();
	return S_OK;
}

int CSkillWindow::Update_GameObject()
{
	// ÇÃ·¹ÀÌ¾î Á¤º¸ ¹Þ¾Æ¿À±â
	m_pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();
	m_UnitInfo = dynamic_cast<CNecromancer*>(m_pPlayer)->Get_Necromancer();

	SkillWndChange();
	
	if (!bisOpenSkillWnd)
		return OBJ_DEAD;
	return 0;
}

void CSkillWindow::Late_Update_GameObject()
{
}

void CSkillWindow::Render_GameObject()
{
	/// º», µ¶ ///
	TCHAR szPlayer_SkillPoint[MAX_PATH] = L"";
	int iPlayer_SkillPoint = m_UnitInfo->iSkillPoint;

	TCHAR szPlayer_Teeth[16] = L"";
	int iPlayer_Teeth = m_UnitInfo->tSkillPoint.Teeth;

	TCHAR szPlayer_BoneArmor[16] = L"";
	int iPlayer_BoneArmor = m_UnitInfo->tSkillPoint.BoneArmor;

	TCHAR szPlayer_PoisonDagger[16] = L"";
	int iPlayer_PoisonDagger = m_UnitInfo->tSkillPoint.PoisonDagger;

	TCHAR szPlayer_CorpseExplosion[16] = L"";
	int iPlayer_CorpseExplosion = m_UnitInfo->tSkillPoint.CorpseExplosion;

	TCHAR szPlayer_BornWall[16] = L"";
	int iPlayer_BornWall = m_UnitInfo->tSkillPoint.BornWall;

	TCHAR szPlayer_PoisonExplosion[16] = L"";
	int iPlayer_PoisonExplosion = m_UnitInfo->tSkillPoint.PoisonExplosion;

	TCHAR szPlayer_BoneSpear[16] = L"";
	int iPlayer_BoneSpear = m_UnitInfo->tSkillPoint.BoneSpear;

	TCHAR szPlayer_BonePrison[16] = L"";
	int iPlayer_BonePrison = m_UnitInfo->tSkillPoint.BonePrison;

	TCHAR szPlayer_PoisonNova[16] = L"";
	int iPlayer_PoisonNova = m_UnitInfo->tSkillPoint.PoisonNova;

	TCHAR szPlayer_BornSpirit[16] = L"";
	int iPlayer_BornSpirit = m_UnitInfo->tSkillPoint.BornSpirit;

	swprintf_s(szPlayer_SkillPoint, __T("%d"), iPlayer_SkillPoint);
	swprintf_s(szPlayer_Teeth, __T("%d"), iPlayer_Teeth);
	swprintf_s(szPlayer_BoneArmor, __T("%d"), iPlayer_BoneArmor);
	swprintf_s(szPlayer_PoisonDagger, __T("%d"), iPlayer_PoisonDagger);
	swprintf_s(szPlayer_CorpseExplosion, __T("%d"), iPlayer_CorpseExplosion);
	swprintf_s(szPlayer_BornWall, __T("%d"), iPlayer_BornWall);
	swprintf_s(szPlayer_PoisonExplosion, __T("%d"), iPlayer_PoisonExplosion);
	swprintf_s(szPlayer_BoneSpear, __T("%d"), iPlayer_BoneSpear);
	swprintf_s(szPlayer_BonePrison, __T("%d"), iPlayer_BonePrison);
	swprintf_s(szPlayer_PoisonNova, __T("%d"), iPlayer_PoisonNova);
	swprintf_s(szPlayer_BornSpirit, __T("%d"), iPlayer_BornSpirit);
	/// º», µ¶ ///

	/// ¼ÒÈ¯ ///

	TCHAR szPlayer_SkeletonMastery[16] = L"";
	int iPlayer_SkeletonMastery = m_UnitInfo->tSummonSkillPoint.SkeletonMastery;

	TCHAR szPlayer_RaiseSkeleton[16] = L"";
	int iPlayer_RaiseSkeleton = m_UnitInfo->tSummonSkillPoint.RaiseSkeleton;

	TCHAR szPlayer_ClayGolem[16] = L"";
	int iPlayer_ClayGolem = m_UnitInfo->tSummonSkillPoint.CrayGolem;

	TCHAR szPlayer_GolemMastery[16] = L"";
	int iPlayer_GolemMastery = m_UnitInfo->tSummonSkillPoint.GolemMastery;

	TCHAR szPlayer_RaiseSkeletonMage[16] = L"";
	int iPlayer_RaiseSkeletonMage = m_UnitInfo->tSummonSkillPoint.RaiseSkeletonMage;

	TCHAR szPlayer_BloodGolem[16] = L"";
	int iPlayer_BloodGolem = m_UnitInfo->tSummonSkillPoint.BloodGolem;

	TCHAR szPlayer_SummonResist[16] = L"";
	int iPlayer_SummonResist = m_UnitInfo->tSummonSkillPoint.SummonResist;

	TCHAR szPlayer_IronGolem[16] = L"";
	int iPlayer_IronGolem = m_UnitInfo->tSummonSkillPoint.IronGolem;

	TCHAR szPlayer_FireGolem[16] = L"";
	int iPlayer_FireGolem = m_UnitInfo->tSummonSkillPoint.FireGolem;

	TCHAR szPlayer_Revive[16] = L"";
	int iPlayer_Revive = m_UnitInfo->tSummonSkillPoint.Revive;

	swprintf_s(szPlayer_SkeletonMastery, __T("%d"), iPlayer_SkeletonMastery);
	swprintf_s(szPlayer_RaiseSkeleton, __T("%d"), iPlayer_RaiseSkeleton);
	swprintf_s(szPlayer_ClayGolem, __T("%d"), iPlayer_ClayGolem);
	swprintf_s(szPlayer_GolemMastery, __T("%d"), iPlayer_GolemMastery);
	swprintf_s(szPlayer_RaiseSkeletonMage, __T("%d"), iPlayer_RaiseSkeletonMage);
	swprintf_s(szPlayer_BloodGolem, __T("%d"), iPlayer_BloodGolem);
	swprintf_s(szPlayer_SummonResist, __T("%d"), iPlayer_SummonResist);
	swprintf_s(szPlayer_IronGolem, __T("%d"), iPlayer_IronGolem);
	swprintf_s(szPlayer_FireGolem, __T("%d"), iPlayer_FireGolem);
	swprintf_s(szPlayer_Revive, __T("%d"), iPlayer_Revive);

	/// ¼ÒÈ¯ ///


	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Single", L"Window", m_dwSkillWndType);
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX - fCenterX - 100, WINCY - fCenterY - 100, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// ½ºÅ³Æ÷ÀÎÆ®
	RECT rSkillPoint = { 130, -190, 230, -160 };
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_SkillPoint, lstrlen(szPlayer_SkillPoint), &rSkillPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	if (m_dwSkillWndType == 3)
	{
		// º»¾Æ¸Ó
		RECT rBoneAumorPoint = { 45, -200, 75, -180 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_BoneArmor, lstrlen(szPlayer_BoneArmor), &rBoneAumorPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// Æ¼½º
		RECT rTeethPoint = { -40, -200, -10, -180 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Teeth, lstrlen(szPlayer_Teeth), &rTeethPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// Æ÷ÀÌÁð´ë°Å
		RECT rPoisonDaggerPoint = { -125, -115, -95, -95 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_PoisonDagger, lstrlen(szPlayer_PoisonDagger), &rPoisonDaggerPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ½ÃÆø
		RECT rCorpseExplosionPoint = { -40, -115, -10, -95 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_CorpseExplosion, lstrlen(szPlayer_CorpseExplosion), &rCorpseExplosionPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// º»¿ù
		RECT rBoneWallPoint = { 45, -26, 75, -6 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_BornWall, lstrlen(szPlayer_BornWall), &rBoneWallPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// Æ÷ÀÌÁðÀÍ½ºÇÁ·Î¼Ç
		RECT rPoisonExplosionPoint = { -125, 61, -95, 81 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_PoisonExplosion, lstrlen(szPlayer_PoisonExplosion), &rPoisonExplosionPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// º»½ºÇÇ¾î
		RECT rBoneSpearPoint = { -40, 61, -10, 81 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_BoneSpear, lstrlen(szPlayer_BoneSpear), &rBoneSpearPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// º»ÇÁ¸®Áð
		RECT rBonePrisonPoint = { 45, 148, 75, 168 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_BonePrison, lstrlen(szPlayer_BonePrison), &rBonePrisonPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// Æ÷ÀÌÁð³ë¹Ù
		RECT rPoisonNovaPoint = { -125, 236, -95, 256 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_PoisonNova, lstrlen(szPlayer_PoisonNova), &rPoisonNovaPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// º»½ºÇÇ¸´
		RECT rBoneSpiritPoint = { -40, 236, -10, 256 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_BornSpirit, lstrlen(szPlayer_BornSpirit), &rBoneSpiritPoint, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	// ¼ÒÈ¯

	if (m_dwSkillWndType == 2)
	{
		// ½ºÄÌ·¹Åæ¸¶½ºÅÍ¸®
		RECT rSkeletonMastery = { -125, -200, -95, -180 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_SkeletonMastery, lstrlen(szPlayer_SkeletonMastery), &rSkeletonMastery, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ·¹ÀÌÁî½ºÄÌ·¹Åæ
		RECT rRaiseSkeleton = { 45, -200, 75, -180 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_RaiseSkeleton, lstrlen(szPlayer_RaiseSkeleton), &rRaiseSkeleton, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// Å¬·¹ÀÌ°ñ·½
		RECT rClayGolem = { -40, -115, -10, -95 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_ClayGolem, lstrlen(szPlayer_ClayGolem), &rClayGolem, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// °ñ·½¸¶½ºÅÍ¸®
		RECT rGolemMastery = { -125, -26, -95, -6 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_GolemMastery, lstrlen(szPlayer_GolemMastery), &rGolemMastery, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ¸ÞÀÌÁö°ñ·½
		RECT rRaiseSkeletonMage = { 45, -26, 75, -6 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_RaiseSkeletonMage, lstrlen(szPlayer_RaiseSkeletonMage), &rRaiseSkeletonMage, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ºí°ñ
		RECT BloodGolem = { -40, 61, -10, 81 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_BloodGolem, lstrlen(szPlayer_BloodGolem), &BloodGolem, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ¼­¸Õ·¹Áö½ºÆ®
		RECT rSummonResist = { -125, 148, -95, 168 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_SummonResist, lstrlen(szPlayer_SummonResist), &rSummonResist, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ¾Æ°ñ
		RECT rIronGolem = { -40, 148, -10, 168 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_IronGolem, lstrlen(szPlayer_IronGolem), &rIronGolem, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ÆÄ°ñ
		RECT rFireGolem = { -40, 236, -10, 256 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_FireGolem, lstrlen(szPlayer_FireGolem), &rFireGolem, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ¸®¹ÙÀÌºê
		RECT rRevive = { 45, 236, 75, 256 };
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szPlayer_Revive, lstrlen(szPlayer_Revive), &rRevive, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	}


}

void CSkillWindow::Release_GameObject()
{
}

void CSkillWindow::SkillWndChange()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_LBUTTON))
	{
		// ½ºÅ³ Ã¢ ´Ý±â
		if (bisOpenSkillWnd)
		{
			if (Get_SkillWndType() == 2)
			{
				if (pt.x > 800 && pt.x < 837 &&
					pt.y > 564 && pt.y < 597)
				{
					bisOpenSkillWnd = false;
				}
			}
			if (Get_SkillWndType() == 3)
			{
				if (pt.x > 993 && pt.x < 1029 &&
					pt.y > 564 && pt.y < 597)
				{
					bisOpenSkillWnd = false;
				}
			}
			if (Get_SkillWndType() == 4)
			{
				if (pt.x > 800 && pt.x < 837 &&
					pt.y > 564 && pt.y < 597)
				{
					bisOpenSkillWnd = false;
				}
			}

			// ¼ÒÈ¯½ºÅ³ Ã¢ ¿­±â
			if (pt.x > 1061 && pt.x < 1176 &&
				pt.y > 210 && pt.y < 335)
				Set_SkillWndType(2);

			// Æ÷ÀÌÁð ½ºÅ³ Ã¢ ¿­±â
			if (pt.x > 1061 && pt.x < 1176 &&
				pt.y > 335 && pt.y < 478)
				Set_SkillWndType(3);

			// ÀúÁÖ ½ºÅ³ Ã¢ ¿­±â
			if (pt.x > 1061 && pt.x < 1176 &&
				pt.y > 478 && pt.y < 610)
				Set_SkillWndType(4);

			if (m_UnitInfo->iSkillPoint <= 0)
				return;

			if (Get_SkillWndType() == 3)
			{
				// Æ¼¾²
				if (pt.x > 885 && pt.x < 944 &&
					pt.y > 90 && pt.y < 148)
				{
					if (m_UnitInfo->tSkillPoint.Teeth >= 20)
						return;
					m_UnitInfo->tSkillCheck.Teeth = true;
					m_UnitInfo->tSkillPoint.Teeth++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.Teeth = true;
				}

				// º»¾Æ¸Ó
				if (pt.x > 970 && pt.x < 1030 &&
					pt.y > 90 && pt.y < 148)
				{
					if (m_UnitInfo->tSkillPoint.BoneArmor >= 20)
						return;
					m_UnitInfo->tSkillCheck.BoneArmor = true;
					m_UnitInfo->tSkillPoint.BoneArmor++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.BoneArmor = true;
				}

				// Æ÷ÀÌÁð´ë°Å
				if (pt.x > 799 && pt.x < 860 &&
					pt.y > 177 && pt.y < 235)
				{
					if (m_UnitInfo->tSkillPoint.PoisonDagger >= 20)
						return;
					m_UnitInfo->tSkillCheck.PoisonDagger = true;
					m_UnitInfo->tSkillPoint.PoisonDagger++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.PoisonDagger = true;
				}

				// ½ÃÆø
				if (pt.x > 885 && pt.x < 944 &&
					pt.y > 177 && pt.y < 235)
				{
					if (m_UnitInfo->tSkillPoint.CorpseExplosion >= 20)
						return;
					m_UnitInfo->tSkillCheck.CorpseExplosion = true;
					m_UnitInfo->tSkillPoint.CorpseExplosion++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.CorpseExplosion = true;
				}

				// bonewall
				if (pt.x > 970 && pt.x < 1030 &&
					pt.y > 263 && pt.y < 324)
				{
					if (m_UnitInfo->tSkillPoint.BornWall >= 20)
						return;
					m_UnitInfo->tSkillCheck.BornWall = true;
					m_UnitInfo->tSkillPoint.BornWall++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.BornWall = true;
				}

				// poison explosion
				if (pt.x > 799 && pt.x < 860 &&
					pt.y > 350 && pt.y < 410)
				{
					if (m_UnitInfo->tSkillPoint.PoisonExplosion >= 20)
						return;
					m_UnitInfo->tSkillCheck.PoisonExplosion = true;
					m_UnitInfo->tSkillPoint.PoisonExplosion++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.PoisonExplosion = true;
				}

				// bonespear
				if (pt.x > 885 && pt.x < 944 &&
					pt.y > 350 && pt.y < 410)
				{
					if (m_UnitInfo->tSkillPoint.BoneSpear >= 20)
						return;
					m_UnitInfo->tSkillCheck.BoneSpear = true;
					m_UnitInfo->tSkillPoint.BoneSpear++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.BoneSpear = true;
				}

				// boneprison
				if (pt.x > 970 && pt.x < 1030 &&
					pt.y > 436 && pt.y < 496)
				{
					if (m_UnitInfo->tSkillPoint.BonePrison >= 20)
						return;
					m_UnitInfo->tSkillCheck.BonePrison = true;
					m_UnitInfo->tSkillPoint.BonePrison++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.BonePrison = true;
				}

				// poisonnova
				if (pt.x > 799 && pt.x < 860 &&
					pt.y > 524 && pt.y < 583)
				{
					if (m_UnitInfo->tSkillPoint.PoisonNova >= 20)
						return;
					m_UnitInfo->tSkillCheck.PoisonNova = true;
					m_UnitInfo->tSkillPoint.PoisonNova++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.PoisonNova = true;
				}

				// bonespirit
				if (pt.x > 885 && pt.x < 944 &&
					pt.y > 524 && pt.y < 583)
				{
					if (m_UnitInfo->tSkillPoint.BornSpirit >= 20)
						return;
					m_UnitInfo->tSkillCheck.BornSpirit = true;
					m_UnitInfo->tSkillPoint.BornSpirit++;
					m_UnitInfo->iSkillPoint--;
					m_UnitInfo->tSkillCheck.BornSpirit = true;
				}
			}

			if (Get_SkillWndType() == 2)
			{
				// ½ºÄÌ·¹Åæ¸¶½ºÅÍ¸®
				if (pt.x > 798 && pt.x < 855 &&
					pt.y > 88 && pt.y < 148)
				{
					if (m_UnitInfo->tSummonSkillPoint.SkeletonMastery >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.SkeletonMastery = true;
					m_UnitInfo->tSummonSkillPoint.SkeletonMastery++;
					m_UnitInfo->iSkillPoint--;
				}

				// ·¹ÀÌÁî ½ºÄÌ·¹Åæ
				if (pt.x > 968 && pt.x < 1032 &&
					pt.y > 88 && pt.y < 148)
				{
					if (m_UnitInfo->tSummonSkillPoint.RaiseSkeleton >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.RaiseSkeleton = true;
					m_UnitInfo->tSummonSkillPoint.RaiseSkeleton++;
					m_UnitInfo->iSkillPoint--;
				}

				// Å¬¤©ÀÌ°ñ·½
				if (pt.x > 884 && pt.x < 942 &&
					pt.y > 175 && pt.y < 231)
				{
					if (m_UnitInfo->tSummonSkillPoint.CrayGolem >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.CrayGolem = true;
					m_UnitInfo->tSummonSkillPoint.CrayGolem++;
					m_UnitInfo->iSkillPoint--;
				}

				// °ñ·½¸¶½ºÅÍ¸®
				if (pt.x > 798 && pt.x < 855 &&
					pt.y > 262 && pt.y < 322)
				{
					if (m_UnitInfo->tSummonSkillPoint.GolemMastery >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.GolemMastery = true;
					m_UnitInfo->tSummonSkillPoint.GolemMastery++;
					m_UnitInfo->iSkillPoint--;
				}

				// ¸ÞÀÌÁö½ºÄÌ·¹Åæ
				if (pt.x > 968 && pt.x < 1032 &&
					pt.y > 262 && pt.y < 322)
				{
					if (m_UnitInfo->tSummonSkillPoint.RaiseSkeletonMage >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.RaiseSkeletonMage = true;
					m_UnitInfo->tSummonSkillPoint.RaiseSkeletonMage++;
					m_UnitInfo->iSkillPoint--;
				}

				// ºí·¯µå°ñ·½
				if (pt.x > 884 && pt.x < 942 &&
					pt.y > 350 && pt.y < 407)
				{
					if (m_UnitInfo->tSummonSkillPoint.BloodGolem >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.BloodGolem = true;
					m_UnitInfo->tSummonSkillPoint.BloodGolem++;
					m_UnitInfo->iSkillPoint--;
				}

				// ¼­¸Õ·¹Áö½ºÆ®
				if (pt.x > 798 && pt.x < 855 &&
					pt.y > 436 && pt.y < 494)
				{
					if (m_UnitInfo->tSummonSkillPoint.SummonResist >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.SummonResist = true;
					m_UnitInfo->tSummonSkillPoint.SummonResist++;
					m_UnitInfo->iSkillPoint--;
				}

				// ¾ÆÀÌ¾ð°ñ·½
				if (pt.x > 884 && pt.x < 942 &&
					pt.y > 436 && pt.y < 494)
				{
					if (m_UnitInfo->tSummonSkillPoint.IronGolem >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.IronGolem = true;
					m_UnitInfo->tSummonSkillPoint.IronGolem++;
					m_UnitInfo->iSkillPoint--;
				}

				// ÆÄ°ñ
				if (pt.x > 884 && pt.x < 942 &&
					pt.y > 521 && pt.y < 584)
				{
					if (m_UnitInfo->tSummonSkillPoint.FireGolem >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.FireGolem = true;
					m_UnitInfo->tSummonSkillPoint.FireGolem++;
					m_UnitInfo->iSkillPoint--;
				}

				// ¸®¹ÙÀÌºê
				if (pt.x > 968 && pt.x < 1032 &&
					pt.y > 521 && pt.y < 584)
				{
					if (m_UnitInfo->tSummonSkillPoint.Revive >= 20)
						return;
					m_UnitInfo->tSummonSkillCheck.Revive = true;
					m_UnitInfo->tSummonSkillPoint.Revive++;
					m_UnitInfo->iSkillPoint--;
				}
			}
		}
	}
}


CGameObject * CSkillWindow::Create()
{
	CGameObject* pInstance = new CSkillWindow;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
