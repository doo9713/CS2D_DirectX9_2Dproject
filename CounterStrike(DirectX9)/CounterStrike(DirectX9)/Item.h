#pragma once

#include "Component.h"

class CItem : public CComponent
{
	RTTICHECK
public :
	void Start();
public :
	CItem(CGameObj* Owner);
	~CItem();
};

