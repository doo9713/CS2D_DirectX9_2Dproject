#pragma once

#include "Controller.h"

class CEnemyController : public CController
{
	RTTICHECK
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
	void ShotGunEffEnd();
};

