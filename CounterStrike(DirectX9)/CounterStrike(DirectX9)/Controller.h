#pragma once

#include "Component.h"

class CAnimation;
class CController : public CComponent
{
	RTTICHECK
protected :
	enum WEAPON
	{
		Weapon_AutoGun,
		Weapon_ShotGun,
		Weapon_Change,
		Weapon_End
	};
	WEAPON Weapon;
	CAnimation* Anim;
	UINT Health;
	double ActionTime;
	double Time;
public :
	_declspec(property(get = _GetHealth, put = _SetHealth)) UINT HEALTH;
	const UINT& _GetHealth() const { return Health; }
	void _SetHealth(UINT health) { Health = health; }
public :
	CController(CGameObj* Owner);
	~CController();
protected : 
	void MakeBullet(double angle);
	void MakeBullet(double angle, float posx, float posy);
	void MakeBlood();
};

