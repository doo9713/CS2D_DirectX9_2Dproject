#include "ArmorItem.h"
#include "GameObj.h"
#include "PlayerController.h"

RTTILINK(CArmorItem, CItem)

void CArmorItem::OnCollisionEnter(CGameObj* Other)
{
	if (Other->Tag == Tag_Player)
	{
		auto player = Other->GetComponent<CPlayerController>();
		player->ARMOR = Clamp(player->ARMOR + 100, 0, 100);
	}
}

CArmorItem::CArmorItem(CGameObj * Owner)
	: CItem(Owner)
{
}

CArmorItem::~CArmorItem()
{
}
