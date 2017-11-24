#include "BulletItem.h"
#include "GameObj.h"
#include "PlayerController.h"

RTTILINK(CBulletItem, CItem)

void CBulletItem::OnCollisionEnter(CGameObj* Other)
{
	if (Other->Tag == Tag_Player)
	{
		auto player = Other->GetComponent<CPlayerController>();
		player->AddBullet();
	}
}

CBulletItem::CBulletItem(CGameObj* Owner)
	: CItem(Owner)
{
}

CBulletItem::~CBulletItem()
{
}
