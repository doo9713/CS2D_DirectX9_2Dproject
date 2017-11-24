#pragma once

#include "Component.h"

class CItem : public CComponent
{
	RTTICHECK
public :
	CItem(CGameObj* Owner);
	~CItem();
};

