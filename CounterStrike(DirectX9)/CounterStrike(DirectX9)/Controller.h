#pragma once

#include "Component.h"

class CController : public CComponent
{
	RTTICHECK
protected :
	UINT Health;
public :
	_declspec(property(get = _GetHealth, put = _SetHealth)) UINT HEALTH;
	const UINT& _GetHealth() const { return Health; }
	void _SetHealth(UINT health) { Health = health; }
public :
	CController(CGameObj* Owner);
	~CController();
};

