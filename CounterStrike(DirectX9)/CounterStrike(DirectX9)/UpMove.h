#pragma once
#include "Move.h"
class CUpMove : public CMove
{
	RTTICHECK
public :
	void Update();
public :
	CUpMove(CGameObj* Owner);
	~CUpMove();
};

