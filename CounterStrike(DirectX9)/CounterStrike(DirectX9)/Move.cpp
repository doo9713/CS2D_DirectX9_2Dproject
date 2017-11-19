#include "Move.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "SpriteRender.h"
#include "Bullet.h"
#include "BoxCollider.h"

RTTILINK(CMove, CComponent)

CMove::CMove(CGameObj* Owner)
	: CComponent(Owner), Speed(200)
{
}

CMove::~CMove()
{
}
