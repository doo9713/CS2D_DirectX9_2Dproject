#include "ShotGunItem.h"
#include "PlayerController.h"
#include "GameObj.h"

RTTILINK(CShotGunItem, CBulletItem)

void CShotGunItem::OnCollisionEnter(CGameObj* Other)
{
	if (Other->Tag == Tag_Player)
	{
		auto player = Other->GetComponent<CPlayerController>();
		player->AddBullet(2);
		player->InvalidateUI();
		Destroy(gameObj);
	}
}

CShotGunItem::CShotGunItem(CGameObj* Owner)
	: CBulletItem(Owner)
{
}

CShotGunItem::~CShotGunItem()
{
}
