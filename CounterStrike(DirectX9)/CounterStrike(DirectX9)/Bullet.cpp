#include "Bullet.h"
#include "GameObj.h"

RTTILINK(CBullet, CComponent)

void CBullet::Update()
{
	gameObj.Position += Dir * TIME.Delta * 900;
}

void CBullet::OnCollisionEnter(CGameObj* Other)
{
	if (Other != Shooter)
		Destroy(gameObj);
}

CBullet::CBullet(CGameObj* Owner)
	: CComponent(Owner), Shooter(nullptr), Dir(1, 0, 0)
{
}

CBullet::~CBullet()
{
}
