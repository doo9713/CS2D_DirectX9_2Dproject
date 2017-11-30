#pragma once

#include "EffectEvent.h"

class CExplosionEffect : public CEffectEvent
{
	RTTICHECK
public :
	void Start();
	void Update();
public :
	CExplosionEffect(CGameObj* Owner);
	~CExplosionEffect();
};

