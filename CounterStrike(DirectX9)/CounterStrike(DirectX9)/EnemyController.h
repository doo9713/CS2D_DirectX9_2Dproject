#pragma once

#include "Controller.h"

class CEnemyController : public CController
{
	RTTICHECK
private :
	float ViewLength;
	CGameObj* Target;
/* Temp Function */
private :
	void Change();
	void ChangeA();
	void ChangeB();
	void Shoot();
/* ------------- */
public :
	void Start();
	void Update();
	void OnCollisionEnter(CGameObj* Other);
public :
	CEnemyController(CGameObj* Owner);
	~CEnemyController();
};

