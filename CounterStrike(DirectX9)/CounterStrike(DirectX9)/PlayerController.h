#pragma once

#include "Controller.h"

class CPlayerController : public CController
{
	RTTICHECK
private :
	double ActionTime;
	double Time;
public :
	void Update();
public :
	CPlayerController(CGameObj* Owner);
	~CPlayerController();
};

