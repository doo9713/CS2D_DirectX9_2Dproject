#pragma once

#include "Ammo.h"

class CGrenade : public CAmmo
{
	RTTICHECK
public :
	void Start();
	void Update();
	void OnCollisionEnter(CGameObj* Owner);
public :
	CGrenade(CGameObj* Other);
	~CGrenade();
public :
	void Explosion();
};

