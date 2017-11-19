#pragma once

#include "Move.h"

class CDownMove : public CMove
{
	RTTICHECK
public :
	void Update();
public :
	CDownMove(CGameObj* Owner);
	~CDownMove();
};

