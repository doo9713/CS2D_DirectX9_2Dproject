#pragma once

#include "Move.h"

class CRightMove : public CMove
{
	RTTICHECK
public :
	void Update();
public :
	CRightMove(CGameObj* Owner);
	~CRightMove();
};

