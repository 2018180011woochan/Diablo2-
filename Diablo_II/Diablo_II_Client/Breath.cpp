#include "stdafx.h"
#include "Breath.h"
#include "Diablo.h"
#include "GameObject_Manager.h"

CBreath::CBreath()
{
}


CBreath::~CBreath()
{
	Release_GameObject();
}

HRESULT CBreath::Ready_GameObject()
{
	return S_OK;
}

int CBreath::Update_GameObject()
{
	m_tBullet.vPos += m_tBullet.vDir * m_tBullet.fSpeed * CTime_Manager::Get_Instance()->Get_TimeDelta();
	m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (m_tBullet.eObjState == OBJ_DEATH)
		return OBJ_DEAD;

	if (m_tBullet.vPos.x > m_vecNecromancerPos.x + (WINCX >> 1) || m_tBullet.vPos.x < m_vecNecromancerPos.x - (WINCX >> 1)
		|| m_tBullet.vPos.y > m_vecNecromancerPos.y + (WINCY >> 1) || m_tBullet.vPos.y < m_vecNecromancerPos.y - (WINCY >> 1))
		return OBJ_DEAD;

	Breath_Update(5.f);

	Update_Monster_Bullet_Rect();
	return OBJ_NOEVENT;
}

void CBreath::Late_Update_GameObject()
{
}

void CBreath::Render_GameObject()
{
	if (m_tBullet.eObjState == OBJ_DEATH)
		return;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"DiaLightning_2", DWORD(m_tBullet.tFrame.fStartFrame));
	if (pTexInfo == nullptr)
		return;
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

void CBreath::Release_GameObject()
{
}

void CBreath::Breath_Update(float fSpeed)
{
	m_tBullet.tFrame.fStartFrame += m_tBullet.tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tBullet.tFrame.fStartFrame > m_tBullet.tFrame.fEndFrame)
		m_tBullet.eObjState = OBJ_DEATH;
}

CGameObject * CBreath::Create(BULLET & _tBullet, _vec3 _Diapos)
{
	CGameObject* pInstance = new CBreath;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CBreath*>(pInstance)->Initialize(_tBullet, _Diapos);
	return pInstance;
}

void CBreath::Initialize(BULLET & _tBullet, _vec3 _Diapos)
{
	// 출발지 = 몬스터위치            목적지 = 플레이어위치
	m_tBullet = _tBullet;
	m_tBullet.vPos = _Diapos;
	m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float Width = abs(m_vecNecromancerPos.x) - abs(m_tBullet.vPos.x);
	float Height = abs(m_vecNecromancerPos.y) - abs(m_tBullet.vPos.y);
	float Distance = sqrt((Width * Width) + (Height * Height));

	m_tBullet.tFrame = { 0.f, 15.f };
	m_tBullet.fSpeed = 1500.f;
	m_tBullet.vSize = { 1.f, 1.f, 0.f };
	m_tBullet.fAttack = 200.f;

	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;

	if ((m_vecNecromancerPos.y - m_tBullet.vPos.y) < 0.f)
		m_tBullet.fBulletImageDir = -(acosf(Width / Distance) /*+ 3.14 / 2.f*/);
	else
		m_tBullet.fBulletImageDir = acosf(Width / Distance)/* - 3.14 / 2.f*/;

	m_tBullet.vDir = m_vecNecromancerPos - m_tBullet.vPos;
	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
}
