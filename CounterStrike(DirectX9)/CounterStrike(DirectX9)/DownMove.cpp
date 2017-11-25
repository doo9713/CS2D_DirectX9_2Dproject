#include "DownMove.h"
#include "GameObj.h"

RTTILINK(CDownMove, CMove)

void CDownMove::Update()
{
	gameObj.Position.y -= TIME.Delta * Speed;
	if (gameObj.Tag == Tag_Player)
		DRX.Camera(gameObj.Position);
}

CDownMove::CDownMove(CGameObj* Owner)
	: CMove(Owner)
{
}


CDownMove::~CDownMove()
{
}
