#include "RightMove.h"
#include "GameObj.h"

RTTILINK(CRightMove, CMove)

void CRightMove::Update()
{
	gameObj.Position.x += TIME.Delta * Speed;
	if (gameObj.Tag == Tag_Player)
		DRX.Camera(gameObj.Position);
}

CRightMove::CRightMove(CGameObj* Owner)
	: CMove(Owner)
{
}

CRightMove::~CRightMove()
{
}
