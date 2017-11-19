#include "EffectEvent.h"
#include "GameObj.h"

RTTILINK(CEffectEvent, CComponent)

CEffectEvent::CEffectEvent(CGameObj* Owner)
	: CComponent(Owner)
{
}

CEffectEvent::~CEffectEvent()
{
}
