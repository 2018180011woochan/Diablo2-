#include "stdafx.h"
#include "PlayerSummonAttack.h"
#include "GameObject_Manager.h"

CPlayerSummonAttack::CPlayerSummonAttack()
{
}


CPlayerSummonAttack::~CPlayerSummonAttack()
{
	Release_GameObject();
}

HRESULT CPlayerSummonAttack::Ready_GameObject()
{
	return S_OK;
}

int CPlayerSummonAttack::Update_GameObject()
{
	m_tBullet.vPos += m_tBullet.vDir * m_tBullet.fSpeed * CTime_Manager::Get_Instance()->Get_TimeDelta();
	_vec3 m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (m_tBullet.eObjState == OBJ_DEATH)
		return OBJ_DEAD;

	if (m_tBullet.vPos.x > m_vecNecromancerPos.x + (WINCX >> 1) || m_tBullet.vPos.x < m_vecNecromancerPos.x - (WINCX >> 1)
		|| m_tBullet.vPos.y > m_vecNecromancerPos.y + (WINCY >> 1) || m_tBullet.vPos.y < m_vecNecromancerPos.y - (WINCY >> 1))
		return OBJ_DEAD;

	FrameMove(0.7f);

	Update_Monster_Bullet_Rect();
	return OBJ_NOEVENT;
}

void CPlayerSummonAttack::Late_Update_GameObject()
{
}

void CPlayerSummonAttack::Render_GameObject()
{
	//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"IceBolt", L"Attack_0", DWORD(m_tFrame.fStartFrame));
	//float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	//float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	//_matrix matScale, matRotZ, matTrans, matWorld;

	//D3DXMatrixScaling(&matScale, m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
	//D3DXMatrixRotationZ(&matRotZ, m_tBullet.fBulletImageDir);
	//D3DXMatrixTranslation(&matTrans, m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
	//matWorld = matScale * matRotZ * matTrans;

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // 여기까지 그린 그림은 Src
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // 여기서부터 그리는 그린 기린그림은 Dest
	//CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	//CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

	//CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void CPlayerSummonAttack::Release_GameObject()
{
}

CGameObject * CPlayerSummonAttack::Create(BULLET & _tBullet, _vec3 _MonsterPos, float _fAttack)
{
	CGameObject* pInstance = new CPlayerSummonAttack;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CPlayerSummonAttack*>(pInstance)->Initialize(_tBullet, _MonsterPos, _fAttack);
	return pInstance;
}

void CPlayerSummonAttack::Initialize(BULLET & _tBullet, _vec3 _MonsterPos, float _fAttack)
{
	m_tBullet = _tBullet;
	m_tBullet.vPos = _MonsterPos;
	m_vecDiaPos = CGameObject_Manager::Get_Instance()->Get_DiabloPos();

	m_tBullet.tFrame = { 0.f, 6.f };
	m_tBullet.fSpeed = 1000.f;
	m_tBullet.vSize = { 1.f, 1.f, 0.f };
	m_tBullet.fAttack = _fAttack;

	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;

	m_tBullet.vDir = m_vecDiaPos - m_tBullet.vPos;
	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
}
