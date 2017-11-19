#pragma once

#include "Component.h"

class CMove : public CComponent
{
	RTTICHECK
protected :
	int Speed;
public :
	CMove(CGameObj* Owner);
	~CMove();
};

