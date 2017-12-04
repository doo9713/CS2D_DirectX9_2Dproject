#include "HealthItem.h"
#include "GameObj.h"
#include "PlayerController.h"

RTTILINK(CHealthItem, CItem)

void CHealthItem::OnCollisionEnter(CGameObj* Other)
{
	if (Other->Tag == Tag_Player)
	{
		auto player = Other->GetComponent<CPlayerController>();
		player->HEALTH = Clamp(player->HEALTH + Random(40, 80), 0, 100);
		player->InvalidateUI();
		Destroy(gameObj);
	}
}

CHealthItem::CHealthItem(CGameObj* Owner)
	: CItem(Owner)
{
}

CHealthItem::~CHealthItem()
{
}
