#include "Item.h"

RTTILINK(CItem, CComponent)

CItem::CItem(CGameObj* Owner)
	: CComponent(Owner)
{
}

CItem::~CItem()
{
}
