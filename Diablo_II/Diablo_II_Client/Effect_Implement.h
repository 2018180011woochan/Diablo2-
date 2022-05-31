#pragma once

#ifndef __EFFECTIMPLEMENT_H__
#define __EFFECTIMPLEMENT_H__

class CEffect_Implement abstract
{
public:
	explicit CEffect_Implement();
	virtual ~CEffect_Implement();

public:
	virtual HRESULT Ready_EffectIMP() PURE;
	virtual int		Update_EffectIMP()PURE;
	virtual void	Render_EffectIMP(const _matrix& rmatWorld)PURE;
	virtual void	Release_EffectIMP()PURE;

protected:
	wstring m_wstrStateKey;
};

#endif // !__EFFECTIMPLEMENT_H__

