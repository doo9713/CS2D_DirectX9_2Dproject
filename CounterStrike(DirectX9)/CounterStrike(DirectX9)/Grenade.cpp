#include "Grenade.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "Animation.h"
#include "SpriteRender.h"
#include "ExplosionEffect.h"
#include "BoxCollider.h"
#include "Rigid.h"

RTTILINK(CGrenade, CAmmo)

void CGrenade::Start()
{
	AddInvoke(CF(Explosion), 1.5);
	Speed = 250;
}

void CGrenade::Update()
{
	gameObj.Position += Dir * TIME.Delta * Speed;
	gameObj.Angle = ClampCycle(gameObj.Angle + TIME.Delta * 500, 0.0, 360.0);
}

void CGrenade::OnCollisionEnter(CGameObj* Other)
{
	if (Other != Shooter)
	{
		if (Other->Tag == Tag_Enemy)
			Explosion();
		else
		{
			AddInvoke(CF(Explosion), 0.5);
			Dir *= -1;
			Speed = 75;
		}
	}
}

CGrenade::CGrenade(CGameObj* Owner)
	: CAmmo(Owner), IsFirstUpdate(true)
{
}

CGrenade::~CGrenade()
{
}

void CGrenade::Explosion()
{
	auto explo = GAMEOBJ.AddGameObj("Explosion", Tag_Effect, Layer_Effect);
	explo->Position = gameObj.Position;
	explo->Scale = VECTOR3(2, 2);

	auto box = explo->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Trigger = true;

	auto csr = explo->AddComponent<CSpriteRender>();
	csr->RenderKey = "Explosion";
	explo->AddComponent<CExplosionEffect>();
	
	auto anim = explo->AddComponent<CAnimation>();
	anim->AnimationName = "ExplosionEffect";

	Destroy(gameObj);
}
