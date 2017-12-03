#pragma once

#include "Ammo.h"

class CGrenade : public CAmmo
{
	RTTICHECK
private :
	bool IsFirstUpdate;
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

