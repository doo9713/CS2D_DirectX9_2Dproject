#pragma once

#include "Controller.h"

class CEnemyController : public CController
{
	RTTICHECK
private :
	CGameObj* Target;
/* Temp Function */
private :
	void Change();
	void ChangeA();
	void ChangeB();
public :
	void Start();
	void Update();
public :
	CEnemyController(CGameObj* Owner);
	~CEnemyController();
};

