#include "GunFireEffect.h"
#include "GameObj.h"
#include "Animation.h"

RTTILINK(CGunFireEffect, CEffectEvent)

void CGunFireEffect::Update()
{
	if (KEY.Down(VK_LBUTTON))
		gameObj.GetComponent<CAnimation>()->AnimationName = "GunFireEffect";
	if (KEY.Pull(VK_LBUTTON))
		gameObj.GetComponent<CAnimation>()->AnimationName = "";
}

CGunFireEffect::CGunFireEffect(CGameObj* Owner)
	: CEffectEvent(Owner)
{
}

CGunFireEffect::~CGunFireEffect()
{
}
