#pragma once

#include "EffectEvent.h"

class CGunFireEffect : public CEffectEvent
{
	RTTICHECK
public :
	void Update();
public :
	CGunFireEffect(CGameObj* Owner);
	~CGunFireEffect();
};

