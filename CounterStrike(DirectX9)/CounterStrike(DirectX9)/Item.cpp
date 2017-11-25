#include "Item.h"
#include "GameObj.h"
#include "BoxCollider.h"

RTTILINK(CItem, CComponent)

void CItem::Start()
{
	gameObj.GetComponent<CBoxCollider>()->Freez = true;
}

CItem::CItem(CGameObj* Owner)
	: CComponent(Owner)
{
}

CItem::~CItem()
{
}
