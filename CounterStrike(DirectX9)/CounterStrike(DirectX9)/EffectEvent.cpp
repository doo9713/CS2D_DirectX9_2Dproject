#include "EffectEvent.h"
#include "GameObj.h"

RTTILINK(CEffectEvent, CComponent)

CEffectEvent::CEffectEvent(CGameObj* Owner)
	: CComponent(Owner), IsLoop(false), lastPage(0)
{
}

CEffectEvent::~CEffectEvent()
{
}
