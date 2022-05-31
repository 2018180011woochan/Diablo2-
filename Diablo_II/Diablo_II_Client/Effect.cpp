#include "stdafx.h"
#include "Effect.h"
#include "Effect_Implement.h"

CEffect::CEffect(CEffect_Implement* pBridge)
	: m_pBridge(pBridge)
{
}


CEffect::~CEffect()
{
	Release_GameObject();
}


void CEffect::Release_GameObject()
{
	Safe_Delete(m_pBridge);
}
