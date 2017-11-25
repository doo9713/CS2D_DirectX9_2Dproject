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
		player->InvalidateUI();
		Destroy(gameObj);
	}
}

CBulletItem::CBulletItem(CGameObj* Owner)
	: CItem(Owner)
{
}

CBulletItem::~CBulletItem()
{
}
