#include "stdafx.h"
#include "BoneSpearEffect.h"
#include "Necromancer.h"
#include "GameObject_Manager.h"

CBoneSpearEffect::CBoneSpearEffect()
	: m_iSkillIndex(0), m_fBoneSpearDir(0.f)
{
}


CBoneSpearEffect::~CBoneSpearEffect()
{
	Release_GameObject();


}

HRESULT CBoneSpearEffect::Ready_GameObject()
{
	m_tBullet.vPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();
	m_tBullet.vSize = { 1.f * m_iSkillIndex, 1.f * m_iSkillIndex, 0.f };
	m_tBullet.vDir = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 9.f };
	m_tBullet.fSpeed = 300.f;

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	//m_vecMouse = { (float)pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (float)pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f };
	m_tBullet.vDir = m_vecMouse - m_tBullet.vPos;

	float Width = abs(m_vecMouse.x) - abs(m_tBullet.vPos.x);
	float Height = abs(m_vecMouse.y) - abs(m_tBullet.vPos.y);
	float Distance = sqrt((Width * Width) + (Height * Height));

	if ((m_vecMouse.y - m_tBullet.vPos.y) < 0.f)
		m_tBullet.fBulletImageDir = -(acosf(Width / Distance) + 3.14 / 2.f);
	else
		m_tBullet.fBulletImageDir = acosf(Width / Distance) - 3.14 / 2.f;

	D3DXVec3Normalize(&m_tBullet.vDir, &m_tBullet.vDir);
	//Update_Dir();
	return S_OK;
}

int CBoneSpearEffect::Update_GameObject()
{
	_vec3 vecPlayerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	m_tBullet.vPos += m_tBullet.vDir * m_tBullet.fSpeed * CTime_Manager::Get_Instance()->Get_TimeDelta();


	Update_Rect();

	if (m_ObjState == OBJ_DEATH)
		return OBJ_DEAD;

	if (m_tBullet.vPos.x > vecPlayerPos.x + (WINCX >> 1) || m_tBullet.vPos.x < vecPlayerPos.x - (WINCX >> 1)
		|| m_tBullet.vPos.y > vecPlayerPos.y + (WINCY >> 1) || m_tBullet.vPos.y < vecPlayerPos.y - (WINCY >> 1))
		return OBJ_DEAD;

	FrameMove(0.5f);
	
	return OBJ_NOEVENT;
}

void CBoneSpearEffect::Late_Update_GameObject()
{
}

void CBoneSpearEffect::Render_GameObject()
{

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"BoneSpearTrail", DWORD(m_tFrame.fStartFrame));
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, m_tBullet.vSize.x, m_tBullet.vSize.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_tBullet.fBulletImageDir);
	D3DXMatrixTranslation(&matTrans, m_tBullet.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tBullet.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
	matWorld = matScale * matRotZ * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->End(); // ������� �׸� �׸��� Src
	CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND); // ���⼭���� �׸��� �׸� �⸰�׸��� Dest
	CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	CGraphic_Device::Get_Instance()->Get_Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void CBoneSpearEffect::Release_GameObject()
{
}

void CBoneSpearEffect::Update_Dir()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	//ClientToScreen(g_hWND, &pt);

	_vec3 vecPlayerPos = CGameObject_Manager::Get_Instance()->Get_NecromancerPos();

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		// Ŀ������ ĳ���Ͱ� ���ʿ� ����
		if (pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) > vecPlayerPos.x)
		{
			// Ŀ������ ĳ���Ͱ� �Ʒ��ʿ� ����
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) > vecPlayerPos.y)
			{
				m_eDir = OBJ_RIGHT_BOTTOM;

				// Ŀ���� ĳ���� y��ǥ�� �����
				if (abs(pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - vecPlayerPos.x) < 50.f)
				{
					m_eDir = OBJ_BOTTOM;
				}
			}
			// Ŀ������ ĳ���Ͱ� ���ʿ� ����
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) < vecPlayerPos.y)
			{
				m_eDir = OBJ_RIGHT_TOP;

				// Ŀ���� ĳ���� y��ǥ�� �����
				if (abs(pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) - vecPlayerPos.x) < 50.f)
				{
					m_eDir = OBJ_TOP;
				}
			}
			// Ŀ���� ĳ���� x��ǥ�� �����
			if (abs(pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - vecPlayerPos.y) < 50.f)
			{
				m_eDir = OBJ_RIGHT;
			}
		}
		// Ŀ������ ĳ���Ͱ� �����ʿ� ����
		if (pt.x + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) < vecPlayerPos.x)
		{

			// Ŀ������ ĳ���Ͱ� �Ʒ��ʿ� ����
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) > vecPlayerPos.y)
			{
				m_eDir = OBJ_LEFT_BOTTOM;

			}
			// Ŀ������ ĳ���Ͱ� ���ʿ� ����
			if (pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) < vecPlayerPos.y)
			{
				m_eDir = OBJ_LEFT_TOP;

			}
			// Ŀ���� ĳ���� x��ǥ�� �����
			if (abs(pt.y + CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - vecPlayerPos.y) < 50.f)
			{
				m_eDir = OBJ_LEFT;
			}
		}



	}
}

CGameObject * CBoneSpearEffect::Create(int _iSkillIndex, _vec3 _Mouse)
{
	CGameObject* pInstance = new CBoneSpearEffect;
	dynamic_cast<CBoneSpearEffect*>(pInstance)->Set_MousePos(_Mouse);
	dynamic_cast<CBoneSpearEffect*>(pInstance)->Set_SkillIndex(_iSkillIndex);
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}
