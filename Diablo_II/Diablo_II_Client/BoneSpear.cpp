#include "stdafx.h"
#include "BoneSpear.h"
#include "Necromancer.h"
#include "GameObject_Manager.h"
#include "BoneSpearEffect.h"
#include "SoundMgr.h"

CBoneSpear::CBoneSpear()
	: m_fBoneSpearDir(0.f)
{
	
}

CBoneSpear::~CBoneSpear()
{
	Release_GameObject();
}

HRESULT CBoneSpear::Ready_GameObject()
{
	//CSoundMgr::Get_Instance()->PlaySound(L"ChargedBolt.wav", CSoundMgr::BONESPEAR);
	return S_OK;
}

int CBoneSpear::Update_GameObject()
{
	_vec3 vecPlayerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();
	CGameObject* pSkill = nullptr;
	CGameObject_Manager*	m_pGameObject_Manager = nullptr;

	m_tBullet.vPos += m_tBullet.vDir * m_tBullet.fSpeed * CTime_Manager::Get_Instance()->Get_TimeDelta();

	float fWidth = abs(vecPlayerPos.x - m_tBullet.vPos.x);
	float fHeight = abs(vecPlayerPos.y - m_tBullet.vPos.y);
	float fDistance = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	if (abs(fDistance) >= 30.f && abs(fDistance) < 40.f)
	{
		pSkill = CBoneSpearEffect::Create(1.0, m_vecMouse);
		if (nullptr != pSkill)
			m_pGameObject_Manager->Get_Instance()->Add_GameObject_Manager(OBJ_EFFECT, pSkill);
	}

	//if (abs(fDistance) >= 50.f && abs(fDistance) < 60.f)
	//{
	//	pSkill = CBoneSpearEffect::Create(2.2, m_vecMouse);
	//	if (nullptr != pSkill)
	//		m_pGameObject_Manager->Get_Instance()->Add_GameObject_Manager(OBJ_EFFECT, pSkill);
	//}

	if (abs(fDistance) >= 70.f && abs(fDistance) < 80.f)
	{
		pSkill = CBoneSpearEffect::Create(1.5, m_vecMouse);
		if (nullptr != pSkill)
			m_pGameObject_Manager->Get_Instance()->Add_GameObject_Manager(OBJ_EFFECT, pSkill);
	}

	//if (abs(fDistance) >= 90.f && abs(fDistance) < 100.f)
	//{
	//	pSkill = CBoneSpearEffect::Create(2.5, m_vecMouse);
	//	if (nullptr != pSkill)
	//		m_pGameObject_Manager->Get_Instance()->Add_GameObject_Manager(OBJ_EFFECT, pSkill);
	//}

	if (abs(fDistance) >= 110.f && abs(fDistance) < 130.f)
	{
		pSkill = CBoneSpearEffect::Create(2.0, m_vecMouse);
		if (nullptr != pSkill)
			m_pGameObject_Manager->Get_Instance()->Add_GameObject_Manager(OBJ_EFFECT, pSkill);
	}

	if (m_tBullet.eObjState == OBJ_DEATH)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BONESPEAR);
		return OBJ_DEAD;
	}

	if (m_tBullet.vPos.x > vecPlayerPos.x + (WINCX >> 1) || m_tBullet.vPos.x < vecPlayerPos.x - (WINCX >> 1)
		|| m_tBullet.vPos.y > vecPlayerPos.y + (WINCY >> 1) || m_tBullet.vPos.y < vecPlayerPos.y - (WINCY >> 1))
		return OBJ_DEAD;

	Update_Player_Bullet_Rect();
	return OBJ_NOEVENT;
}

void CBoneSpear::Late_Update_GameObject()
{
	FrameMove(0.7f);
}

void CBoneSpear::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"BoneSpear", DWORD(m_tBullet.tFrame.fStartFrame));
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale,m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_tBullet.fBulletImageDir);
	D3DXMatrixTranslation(&matTrans, m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
	matWorld = matScale * matRotZ * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
	CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
	CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void CBoneSpear::Release_GameObject()
{
}

CGameObject * CBoneSpear::Create(BULLET& _tBullet)
{
	CGameObject* pInstance = new CBoneSpear;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CBoneSpear*>(pInstance)->Initialize(_tBullet);
	return pInstance;
}

void CBoneSpear::Initialize(BULLET & _tBullet)
{
	m_tBullet = _tBullet;
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	m_tBullet.vPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	m_vecMouse = { (float)pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (float)pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f };

	float Width = abs(m_vecMouse.x) - abs(m_tBullet.vPos.x);
	float Height = abs(m_vecMouse.y) - abs(m_tBullet.vPos.y);
	float Distance = sqrt((Width * Width) + (Height * Height));


	m_tBullet.tFrame = { 0.f, 6.f };
	m_tBullet.fSpeed = 300.f;
	m_tBullet.vSize = { 2.f, 2.f, 0.f };

	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;

	if ((m_vecMouse.y - m_tBullet.vPos.y) < 0.f)
		m_tBullet.fBulletImageDir = -(acosf(Width / Distance) + 3.14 / 2.f);
	else
		m_tBullet.fBulletImageDir = acosf(Width / Distance) - 3.14 / 2.f;

	m_tBullet.vDir = m_vecMouse - m_tBullet.vPos;
	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
	m_tBullet.fAttack = 200.f;
}
