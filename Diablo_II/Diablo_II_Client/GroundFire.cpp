#include "stdafx.h"
#include "GroundFire.h"
#include "Diablo.h"
#include "GameObject_Manager.h"

CGroundFire::CGroundFire()
{
}


CGroundFire::~CGroundFire()
{
	Release_GameObject();
}

HRESULT CGroundFire::Ready_GameObject()
{
	return S_OK;
}

int CGroundFire::Update_GameObject()
{
	_vec3 vecPlayerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	m_tBullet.vPos += m_tBullet.vDir * m_tBullet.fSpeed * CTime_Manager::Get_Instance()->Get_TimeDelta();

	if (m_tBullet.eObjState == OBJ_DEATH)
		return OBJ_DEAD;

	if (m_tBullet.vPos.x > vecPlayerPos.x + (WINCX >> 1) + 500 || m_tBullet.vPos.x < vecPlayerPos.x - ((WINCX >> 1) + 500)
		|| m_tBullet.vPos.y > vecPlayerPos.y + (WINCY >> 1) || m_tBullet.vPos.y < vecPlayerPos.y - (WINCY >> 1))
		return OBJ_DEAD;

	Update_Monster_Bullet_Rect();
	return OBJ_NOEVENT;
}

void CGroundFire::Late_Update_GameObject()
{
	Breath_Update(0.1f);
}

void CGroundFire::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"GroundFire", DWORD(m_tFrame.fStartFrame));
	if (pTexInfo == nullptr)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
	matWorld = matScale * matTrans;

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

void CGroundFire::Release_GameObject()
{
}

void CGroundFire::Breath_Update(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		m_tBullet.eObjState = OBJ_DEATH;
}

CGameObject * CGroundFire::Create(BULLET & _tBullet, _vec3 _Diapos)
{
	CGameObject* pInstance = new CGroundFire;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CGroundFire*>(pInstance)->Initialize(_tBullet, _Diapos);
	return pInstance;
}

void CGroundFire::Initialize(BULLET & _tBullet, _vec3 _Diapos)
{
	// 출발지 = 몬스터위치            목적지 = 플레이어위치
	m_tBullet = _tBullet;
	m_tBullet.vPos = CGameObject_Manager::Get_Instance()->Get_DiabloPos();
	m_vecNecromancerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	float Width = abs(_Diapos.x) - abs(m_tBullet.vPos.x);
	float Height = abs(_Diapos.y) - abs(m_tBullet.vPos.y);
	float Distance = sqrt((Width * Width) + (Height * Height));

	m_tBullet.tFrame = { 10.f, 37.f };
	m_tBullet.fSpeed = 200.f;
	m_tBullet.vSize = { 1.f, 1.f, 0.f };
	m_tBullet.fAttack = 200.f;

	m_tFrame = m_tBullet.tFrame;

	m_tRect.top = m_tBullet.vPos.y - 20.f;
	m_tRect.left = m_tBullet.vPos.x - 20.f;
	m_tRect.bottom = m_tBullet.vPos.y + 20.f;
	m_tRect.right = m_tBullet.vPos.x + 20.f;

	m_tBullet.vDir = _Diapos - m_tBullet.vPos;
	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
}
