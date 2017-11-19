#pragma once

#include "Component.h"

class CEffectEvent : public CComponent
{
	RTTICHECK
public :
	CEffectEvent(CGameObj* Owner);
	~CEffectEvent();
};

