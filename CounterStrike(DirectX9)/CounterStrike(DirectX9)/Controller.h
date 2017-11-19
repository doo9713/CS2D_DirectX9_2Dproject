#pragma once

#include "Component.h"

class CController : public CComponent
{
	RTTICHECK
public :
	CController(CGameObj* Owner);
	~CController();
};

