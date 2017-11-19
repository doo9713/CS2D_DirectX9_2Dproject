#pragma once

#include "Move.h"

class CLeftMove : public CMove
{
	RTTICHECK
public :
	void Update();
public :
	CLeftMove(CGameObj* Owner);
	~CLeftMove();
};

