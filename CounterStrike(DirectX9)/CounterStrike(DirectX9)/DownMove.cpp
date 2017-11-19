#include "DownMove.h"
#include "GameObj.h"

RTTILINK(CDownMove, CMove)

void CDownMove::Update()
{
	gameObj.Position.y -= TIME.Delta * Speed;
}

CDownMove::CDownMove(CGameObj* Owner)
	: CMove(Owner)
{
}


CDownMove::~CDownMove()
{
}
