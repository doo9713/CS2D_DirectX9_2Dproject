#include "LeftMove.h"
#include "GameObj.h"

RTTILINK(CLeftMove, CMove)

void CLeftMove::Update()
{
	gameObj.Position.x -= TIME.Delta * Speed;
}

CLeftMove::CLeftMove(CGameObj* Owner)
	: CMove(Owner)
{
}

CLeftMove::~CLeftMove()
{
}
