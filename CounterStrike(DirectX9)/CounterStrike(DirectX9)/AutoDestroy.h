#pragma once

#include "Component.h"

class CAutoDestroy : public CComponent
{
	RTTICHECK
public :
	void Auto();
	void Start();
public :
	CAutoDestroy(CGameObj* Owner);
	~CAutoDestroy();
};

