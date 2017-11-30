#include "Grenade.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "Animation.h"
#include "SpriteRender.h"
#include "ExplosionEffect.h"

RTTILINK(CGrenade, CAmmo)

void CGrenade::Start()
{
	AddInvoke(OCF(Explosion, gameObj), 1.5);
	Speed = 200;
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
		AddInvoke(OCF(Explosion, gameObj), 0.5);
		Dir.y *= -1;
		Speed = 75;
	}
}

CGrenade::CGrenade(CGameObj* Owner)
	: CAmmo(Owner)
{
}

CGrenade::~CGrenade()
{
}

void CGrenade::Explosion(CGameObj& obj)
{
	auto explo = GAMEOBJ.AddGameObj("Explosion", Tag_Effect, Layer_Effect);
	explo->Position = gameObj.Position;
	explo->Scale = VECTOR3(2, 2);
	
	auto csr = explo->AddComponent<CSpriteRender>();
	csr->RenderKey = "Explosion";
	explo->AddComponent<CExplosionEffect>();
	
	auto anim = explo->AddComponent<CAnimation>();
	anim->AnimationName = "ExplosionEffect";

	Destroy(obj);
}
