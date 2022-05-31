#include "stdafx.h"
#include "SK2_Skill.h"
#include "Necromancer.h"
#include "GameObject.h"
#include "SK2.h"
#include "GameObject_Manager.h"

SK2_Skill::SK2_Skill()
{
}


SK2_Skill::~SK2_Skill()
{
	Release_GameObject();
}

HRESULT SK2_Skill::Ready_GameObject()
{
	return S_OK;
}

int SK2_Skill::Update_GameObject()
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

void SK2_Skill::Late_Update_GameObject()
{
}

void SK2_Skill::Render_GameObject()
{
	if (m_tBullet.eObjState == OBJ_DEATH)
		return;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"IceBolt", L"Attack_0", DWORD(m_tFrame.fStartFrame));
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
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

void SK2_Skill::Release_GameObject()
{
}

CGameObject * SK2_Skill::Create(BULLET _tBullet, _vec3 _SK2Pos)
{
	CGameObject* pInstance = new SK2_Skill;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<SK2_Skill*>(pInstance)->Initialize(_tBullet, _SK2Pos);
	return pInstance;
}

void SK2_Skill::Initialize(BULLET & _tBullet, _vec3 _SK2Pos)
{
	// 출발지 = 몬스터위치            목적지 = 플레이어위치
	m_tBullet = _tBullet;
	m_tBullet.vPos = _SK2Pos;
	m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float Width = abs(m_vecNecromancerPos.x) - abs(m_tBullet.vPos.x);
	float Height = abs(m_vecNecromancerPos.y) - abs(m_tBullet.vPos.y);
	float Distance = sqrt((Width * Width) + (Height * Height));

	m_tBullet.tFrame = { 0.f, 6.f };
	m_tBullet.fSpeed = 300.f;
	m_tBullet.vSize = { 2.f, 2.f, 0.f };
	m_tBullet.fSpeed = 300.f;
	m_tBullet.fAttack = 200.f;

	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;

	if ((m_vecNecromancerPos.y - m_tBullet.vPos.y) < 0.f)
		m_tBullet.fBulletImageDir = -(acosf(Width / Distance) + 3.14 / 2.f);
	else
		m_tBullet.fBulletImageDir = acosf(Width / Distance) - 3.14 / 2.f;

	m_tBullet.vDir = m_vecNecromancerPos - m_tBullet.vPos;
	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
}
