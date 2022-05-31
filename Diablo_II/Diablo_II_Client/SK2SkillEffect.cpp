#include "stdafx.h"
#include "SK2SkillEffect.h"


CSK2SkillEffect::CSK2SkillEffect()
{
}


CSK2SkillEffect::~CSK2SkillEffect()
{
	Release_GameObject();
}

void CSK2SkillEffect::Effect_FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tFrame.fStartFrame >m_tFrame.fEndFrame)
		m_tEffect.bisDead = true;

}

HRESULT CSK2SkillEffect::Ready_GameObject()
{
	return S_OK;
}

int CSK2SkillEffect::Update_GameObject()
{
	if (m_tEffect.bisDead)
		return OBJ_DEAD;

	Effect_FrameMove(1.f);
	return OBJ_NOEVENT;
}

void CSK2SkillEffect::Late_Update_GameObject()
{
}

void CSK2SkillEffect::Render_GameObject()
{
	if (m_tEffect.bisDead)
		return;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Skill", L"IceStromImpact2", DWORD(m_tFrame.fStartFrame));
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	_matrix matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, m_tEffect.vSize.x, m_tEffect.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tEffect.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tEffect.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
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

void CSK2SkillEffect::Release_GameObject()
{
}

CGameObject * CSK2SkillEffect::Create(EFFECT _tEffect, _vec3 _SK2BulletPos)
{
	CGameObject* pInstance = new CSK2SkillEffect;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	dynamic_cast<CSK2SkillEffect*>(pInstance)->Initialize(_tEffect, _SK2BulletPos);
	return pInstance;
}

void CSK2SkillEffect::Initialize(EFFECT _tEffect, _vec3 _SK2BulletPos)
{
	m_tEffect = _tEffect;
	m_tEffect.vPos = _SK2BulletPos;
	m_tEffect.vSize = { 1.f, 1.f, 0.f };
	m_tEffect.tFrame = { 0.f, 6.f };
	m_tEffect.bisDead = false;
	m_tEffect.fSpeed = 10.f;

	m_tFrame = m_tEffect.tFrame;
}
