#include "UpMove.h"
#include "GameObj.h"

RTTILINK(CUpMove, CMove)

void CUpMove::Update()
{
	gameObj.Position.y += TIME.Delta * Speed;
	if (gameObj.Tag == Tag_Player)
		DRX.Camera(gameObj.Position);
}

CUpMove::CUpMove(CGameObj* Owner)
	: CMove(Owner)
{
}

CUpMove::~CUpMove()
{
}
