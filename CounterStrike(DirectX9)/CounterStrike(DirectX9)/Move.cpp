#include "Move.h"
#include "GameObj.h"

RTTILINK(CMove, CComponent)

void CMove::Update()
{
	/* Rotation to Mouse Position */
	VECTOR3 Mouse = GetMousePosition();
	MATRIX Matrix;
	DRX->GetTransform(D3DTS_VIEW, &Matrix);	// 게임 맵 전체 좌표 기준으로 맞춤
	Mouse.TransformCoord(Matrix);
	gameObj.Angle = Angle(Mouse - gameObj.Position);

	if (KEY.Down('S'))
		gameObj.Position.y -= TIME.Delta * 100;
	if (KEY.Down('W'))
		gameObj.Position.y += TIME.Delta * 100;
	if (KEY.Down('D'))
		gameObj.Position.x += TIME.Delta * 100;
	if (KEY.Down('A'))
		gameObj.Position.x -= TIME.Delta * 100;
}

CMove::CMove(CGameObj* Owner)
	: CComponent(Owner)
{
}

CMove::~CMove()
{
}
