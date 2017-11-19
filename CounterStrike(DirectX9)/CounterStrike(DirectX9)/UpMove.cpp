#include "UpMove.h"
#include "GameObj.h"

RTTILINK(CUpMove, CMove)

void CUpMove::Update()
{
	gameObj.Position.y += TIME.Delta * Speed;
}

CUpMove::CUpMove(CGameObj* Owner)
	: CMove(Owner)
{
}

CUpMove::~CUpMove()
{
}
