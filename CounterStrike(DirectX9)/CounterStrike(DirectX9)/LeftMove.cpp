#include "LeftMove.h"
#include "GameObj.h"

RTTILINK(CLeftMove, CMove)

void CLeftMove::Update()
{
	gameObj.Position.x -= TIME.Delta * Speed;
	if (gameObj.Tag == Tag_Player)
		DRX.Camera(gameObj.Position);
}

CLeftMove::CLeftMove(CGameObj* Owner)
	: CMove(Owner)
{
}

CLeftMove::~CLeftMove()
{
}
