#include "BoxCollider.h"
#include "GameObj.h"

RTTILINK(CBoxCollider, CComponent)

bool CBoxCollider::LineSplit(const VECTOR3* ABox, const VECTOR3* BBox, MATRIX AWorld, MATRIX BWorld)
{
	VECTOR3 Src[4];
	memcpy(Src, BBox, sizeof(Src));
	AWorld.Inverse();
	for (int i = 0; i < 4; ++i)
	{
		Src[i].TransformCoord(BWorld);
		Src[i].TransformCoord(AWorld);
	}

	VECTOR3 Min(
		MinList({ Src[0].x, Src[1].x, Src[2].x, Src[3].x }),
		MinList({ Src[0].y, Src[1].y, Src[2].y, Src[3].y })
	);
	VECTOR3 Max(
		MaxList({ Src[0].x, Src[1].x, Src[2].x, Src[3].x }),
		MaxList({ Src[0].y, Src[1].y, Src[2].y, Src[3].y })
	);

	if (Min.x > ABox[2].x) return false;
	if (ABox[0].x > Max.x) return false;
	if (Min.y > ABox[0].y) return false;
	if (ABox[2].y > Max.y) return false;
	return true;
}

void CBoxCollider::PushCheck(const VECTOR3 * Box, const VECTOR3 & Pivot, const VECTOR3 & OtherPrivot, CBoxCollider * Other)
{
	float AngleArray[4] =
	{
		Angle(Box[0] - Pivot),
		Angle(Box[1] - Pivot),
		Angle(Box[2] - Pivot),
		Angle(Box[3] - Pivot)
	};

	float TargetAngle = Angle(OtherPrivot - Pivot);
	int Low = MinIndex({ AngleArray[0], AngleArray[1], AngleArray[2], AngleArray[3] });
	Low += 4;

	VECTOR3 CenterPos;

	if (AngleArray[(Low + 0) % 4] > TargetAngle || TargetAngle > AngleArray[(Low + 1) % 4])
	{
		CenterPos = (Box[(Low + 0) % 4] + Box[(Low + 1) % 4]) * 0.5;
		CenterPos = CenterPos - Pivot;
		CGameObj* Temp = &Other->gameObj;
		while (Temp->Parent) Temp = Temp->Parent;
		Temp->Position += CenterPos.Normalize() * TIME.Delta * 1000;
		return;
	}
	if (AngleArray[(Low - 1) % 4] > TargetAngle || TargetAngle > AngleArray[(Low + 0) % 4])
	{
		CenterPos = (Box[(Low - 1) % 4] + Box[(Low + 0) % 4]) * 0.5;
		CenterPos = CenterPos - Pivot;
		CGameObj* Temp = &Other->gameObj;
		while (Temp->Parent) Temp = Temp->Parent;
		Temp->Position += CenterPos.Normalize() * TIME.Delta * 1000;
		return;
	}
	if (AngleArray[(Low + 1) % 4] > TargetAngle || TargetAngle > AngleArray[(Low + 2) % 4])
	{
		CenterPos = (Box[(Low + 1) % 4] + Box[(Low + 2) % 4]) * 0.5;
		CenterPos = CenterPos - Pivot;
		CGameObj* Temp = &Other->gameObj;
		while (Temp->Parent) Temp = Temp->Parent;
		Temp->Position += CenterPos.Normalize() * TIME.Delta * 1000;
		return;
	}
	if (AngleArray[(Low + 2) % 4] > TargetAngle || TargetAngle > AngleArray[(Low - 1) % 4])
	{
		CenterPos = (Box[(Low + 2) % 4] + Box[(Low - 1) % 4]) * 0.5;
		CenterPos = CenterPos - Pivot;
		CGameObj* Temp = &Other->gameObj;
		while (Temp->Parent) Temp = Temp->Parent;
		Temp->Position += CenterPos.Normalize() * TIME.Delta * 1000;
		return;
	}
}

void CBoxCollider::BoxPushBox(CBoxCollider * Other)
{
	if (Freez && Other->Freez)
		return;

	VECTOR3 Box[4] =
	{
		{ -Size.x * 0.5f, +Size.y * 0.5f, 0 },
		{ +Size.x * 0.5f, +Size.y * 0.5f, 0 },
		{ +Size.x * 0.5f, -Size.y * 0.5f, 0 },
		{ -Size.x * 0.5f, -Size.y * 0.5f, 0 }
	};
	VECTOR3 OtherBox[4] =
	{
		{ -Other->Size.x * 0.5f, +Other->Size.y * 0.5f, 0 },
		{ +Other->Size.x * 0.5f, +Other->Size.y * 0.5f, 0 },
		{ +Other->Size.x * 0.5f, -Other->Size.y * 0.5f, 0 },
		{ -Other->Size.x * 0.5f, -Other->Size.y * 0.5f, 0 }
	};
	MATRIX World, OtherWorld;
	World = World.Move(Center) * gameObj.World;
	OtherWorld = OtherWorld.Move(Other->Center) * Other->gameObj.World;

	for (int i = 0; i < 4; ++i)
	{
		Box[i].TransformCoord(World);
		OtherBox[i].TransformCoord(OtherWorld);
	}

	VECTOR3 Pivot, OtherPivot;
	Pivot.TransformCoord(World);
	OtherPivot.TransformCoord(OtherWorld);

	if (!Other->Freez)
		PushCheck(Box, Pivot, OtherPivot, Other);
	if (!Freez)
		PushCheck(OtherBox, OtherPivot, Pivot, this);
}

bool CBoxCollider::BoxToPoint(VECTOR3 & Point)
{
	VECTOR3 Box[4] =
	{
		{ -Size.x * 0.5f, +Size.y * 0.5f, 0 },
		{ +Size.x * 0.5f, +Size.y * 0.5f, 0 },
		{ +Size.x * 0.5f, -Size.y * 0.5f, 0 },
		{ -Size.x * 0.5f, -Size.y * 0.5f, 0 }
	};

	MATRIX World;
	World = World.Move(Center) * gameObj.World;
	World.Inverse();
	Point.TransformCoord(World);
	if (Box[0].x < Point.x && Box[2].x > Point.x && Box[0].y > Point.y && Box[2].y < Point.y)
		return true;
	return false;
}

bool CBoxCollider::BoxToBox(const CBoxCollider * Other)
{
	VECTOR3 Box[4] =
	{
		{ -Size.x * 0.5f, +Size.y * 0.5f, 0 },
		{ +Size.x * 0.5f, +Size.y * 0.5f, 0 },
		{ +Size.x * 0.5f, -Size.y * 0.5f, 0 },
		{ -Size.x * 0.5f, -Size.y * 0.5f, 0 }
	};
	VECTOR3 OtherBox[4] =
	{
		{ -Other->Size.x * 0.5f, +Other->Size.y * 0.5f, 0 },
		{ +Other->Size.x * 0.5f, +Other->Size.y * 0.5f, 0 },
		{ +Other->Size.x * 0.5f, -Other->Size.y * 0.5f, 0 },
		{ -Other->Size.x * 0.5f, -Other->Size.y * 0.5f, 0 }
	};

	MATRIX World, OtherWorld;
	World = World.Move(Center) * gameObj.World;
	OtherWorld = OtherWorld.Move(Other->Center) * Other->gameObj.World;

	if (!LineSplit(Box, OtherBox, World, OtherWorld))
		return false;
	if (!LineSplit(OtherBox, Box, OtherWorld, World))
		return false;
	return true;
}

CBoxCollider::CBoxCollider(CGameObj * Owner)
	: CComponent(Owner), Freez(false), Center(0, 0, 0), Size(0, 0, 0)
{
}

CBoxCollider::~CBoxCollider()
{
}
