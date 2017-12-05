#include "AutoGunItem.h"
#include "PlayerController.h"
#include "GameObj.h"

RTTILINK(CAutoGunItem, CBulletItem)

void CAutoGunItem::OnCollisionEnter(CGameObj* Other)
{
	if (Other->Tag == Tag_Player)
	{
		auto player = Other->GetComponent<CPlayerController>();
		player->AddBullet(1);
		player->InvalidateUI();
		Destroy(gameObj);
	}
}

CAutoGunItem::CAutoGunItem(CGameObj* Owner)
	:CBulletItem(Owner)
{
}

CAutoGunItem::~CAutoGunItem()
{
}
