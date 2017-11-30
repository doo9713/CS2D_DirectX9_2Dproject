#include "Ammo.h"

RTTILINK(CAmmo, CComponent)

CAmmo::CAmmo(CGameObj* Owner)
	: CComponent(Owner), Shooter(nullptr), Dir(1, 0, 0), Speed(0)
{
}

CAmmo::~CAmmo()
{
}
