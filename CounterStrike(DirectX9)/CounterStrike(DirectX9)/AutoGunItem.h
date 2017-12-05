#pragma once

#include "BulletItem.h"

class CAutoGunItem : public CBulletItem
{
	RTTICHECK
public :
	void OnCollisionEnter(CGameObj* Other);
public :
	CAutoGunItem(CGameObj* Owner);
	~CAutoGunItem();
};

