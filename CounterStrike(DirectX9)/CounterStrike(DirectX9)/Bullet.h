#pragma once
#include "Ammo.h"

class CBullet :	public CAmmo
{
	RTTICHECK
public :
	void Start();
	void Update();
	void OnCollisionEnter(CGameObj* Other);
public :
	CBullet(CGameObj* Owner);
	~CBullet();
};

