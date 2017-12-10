#pragma once

#include "Controller.h"

class CEnemyController : public CController
{
	RTTICHECK
public :
	static int EnemyCnt;
private :
	float ViewLength;
	double rate;
	double firstAngle;
	double dstAngle;
	CGameObj* Target;
public :
	void Start();
	void Update();
	void OnCollisionEnter(CGameObj* Other);
public :
	CEnemyController(CGameObj* Owner);
	~CEnemyController();
private :
	void MakeItem(WEAPON myWeapon);
	void ShotGunEffEnd();
};

