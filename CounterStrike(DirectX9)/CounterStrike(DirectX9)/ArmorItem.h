#pragma once

#include "Item.h"

class CArmorItem : public CItem
{
	RTTICHECK
public :
	void OnCollisionEnter(CGameObj* Other);
public :
	CArmorItem(CGameObj* Owner);
	~CArmorItem();
};

