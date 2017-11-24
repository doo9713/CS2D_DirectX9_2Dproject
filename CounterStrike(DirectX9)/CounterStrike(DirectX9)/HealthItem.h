#pragma once

#include "Item.h"

class CHealthItem :	public CItem
{
	RTTICHECK
public :
	void OnCollisionEnter(CGameObj* Other);
public :
	CHealthItem(CGameObj* Owner);
	~CHealthItem();
};

