#pragma once

#include "Item.h"

class CBulletItem :	public CItem
{
	RTTICHECK
public :
	void OnCollisionEnter(CGameObj* Other);
public :
	CBulletItem(CGameObj* Owner);
	~CBulletItem();
};

