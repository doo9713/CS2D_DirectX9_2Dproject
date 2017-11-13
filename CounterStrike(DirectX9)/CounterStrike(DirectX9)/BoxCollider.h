#pragma once

#include "Component.h"

class CBoxCollider : public CComponent
{
	RTTICHECK
private :
	bool LineSplit(const VECTOR3* ABox, const VECTOR3* BBox, MATRIX AWorld, MATRIX BWorld);
	void PushCheck(const VECTOR3* Box, const VECTOR3& Pivot, const VECTOR3& OtherPrivot, CBoxCollider* Other);
public :
	bool Freez;
	VECTOR3 Center;
	VECTOR3 Size;
public :
	void BoxPushBox(CBoxCollider* Other);
	bool BoxToPoint(VECTOR3& Point);
	bool BoxToBox(const CBoxCollider* Other);
public :
	CBoxCollider(CGameObj* Owner);
	~CBoxCollider();
};

