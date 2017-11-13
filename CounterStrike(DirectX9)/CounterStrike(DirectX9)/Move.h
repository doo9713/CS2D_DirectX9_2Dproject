#pragma once

#include "Component.h"

class CMove : public CComponent
{
	RTTICHECK
public :
	void Update();
public :
	CMove(CGameObj* Owner);
	~CMove();
};

