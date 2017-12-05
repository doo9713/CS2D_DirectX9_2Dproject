#pragma once

#include "BulletItem.h"

class CShotGunItem : public CBulletItem
{
	RTTICHECK
public:
	void OnCollisionEnter(CGameObj* Other);
public :
	CShotGunItem(CGameObj* Owner);
	~CShotGunItem();
};

