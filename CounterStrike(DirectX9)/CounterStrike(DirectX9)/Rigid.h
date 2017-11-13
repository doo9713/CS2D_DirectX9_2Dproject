#pragma once

#include "Component.h"

class CBoxCollider;
class CRigid : public CComponent
{
	RTTICHECK
private :
	CBoxCollider* Collider;
	VECTOR3 Force;
	list<CGameObj*> Collision;
	list<CGameObj*> PrevCollision;
private :
	bool IsPrevIn(CGameObj* Other);
	bool IsIn(CGameObj* Other);
public :
	void AddForce(const VECTOR3& Force) { this->Force += Force; }
	void SetForce(const VECTOR3& Force) { this->Force = Force; }
	void ResetForce() { this->Force = VECTOR3(0, 0, 0); }
public :
	void Start();
	void Update();
public :
	CRigid(CGameObj* Owner);
	~CRigid();
};

