#pragma once

#include "Component.h"

class CAmmo : public CComponent
{
	RTTICHECK
protected :
	UINT Speed;
public :
	VECTOR3 Dir;
	CGameObj* Shooter;
public :
	CAmmo(CGameObj* Owner);
	~CAmmo();
};

