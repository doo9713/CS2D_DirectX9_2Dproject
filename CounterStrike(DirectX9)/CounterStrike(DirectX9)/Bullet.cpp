#include "Bullet.h"
#include "GameObj.h"

RTTILINK(CBullet, CAmmo)

void CBullet::Start()
{
	AddInvoke(OCF(Destroy, gameObj), 2);
	Speed = 900;
}

void CBullet::Update()
{
	gameObj.Position += Dir * TIME.Delta * Speed;
}

void CBullet::OnCollisionEnter(CGameObj* Other)
{
	if (Other != Shooter)
		Destroy(gameObj);
}

CBullet::CBullet(CGameObj* Owner)
	: CAmmo(Owner)
{
}

CBullet::~CBullet()
{
}
