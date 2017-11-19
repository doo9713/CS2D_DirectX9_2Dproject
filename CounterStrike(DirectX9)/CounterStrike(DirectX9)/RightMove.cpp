#include "RightMove.h"
#include "GameObj.h"

RTTILINK(CRightMove, CMove)

void CRightMove::Update()
{
	gameObj.Position.x += TIME.Delta * Speed;
}

CRightMove::CRightMove(CGameObj* Owner)
	: CMove(Owner)
{
}

CRightMove::~CRightMove()
{
}
