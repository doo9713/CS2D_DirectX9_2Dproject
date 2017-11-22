#pragma once
#include "Component.h"

class CBullet :	public CComponent
{
	RTTICHECK
private :
	FLOAT Angle;
public :
	VECTOR3 Dir;
	CGameObj* Shooter;
public :
	void Update();
	void OnCollisionEnter(CGameObj* Other);
public :
	CBullet(CGameObj* Owner);
	~CBullet();
};

