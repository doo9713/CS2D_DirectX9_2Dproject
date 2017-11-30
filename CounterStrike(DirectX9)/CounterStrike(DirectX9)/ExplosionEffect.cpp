#include "ExplosionEffect.h"
#include "SpriteRender.h"
#include "GameObj.h"

RTTILINK(CExplosionEffect, CEffectEvent)

void CExplosionEffect::Start()
{
	lastPage = 9;
	CSR = gameObj.GetComponent<CSpriteRender>();
}

void CExplosionEffect::Update()
{
	if (CSR)
	{
		if (CSR->Page == lastPage)
			Destroy(gameObj);
	}
}

CExplosionEffect::CExplosionEffect(CGameObj* Owner)
	: CEffectEvent(Owner)
{
}

CExplosionEffect::~CExplosionEffect()
{
}
