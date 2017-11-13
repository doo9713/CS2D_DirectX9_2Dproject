#include "AutoDestroy.h"

RTTILINK(CAutoDestroy, CComponent)

void CAutoDestroy::Auto()
{
	Destroy(gameObj);
}

void CAutoDestroy::Start()
{
	AddInvoke(CF(Auto), 0.1);
}

CAutoDestroy::CAutoDestroy(CGameObj * Owner)
	: CComponent(Owner)
{
}

CAutoDestroy::~CAutoDestroy()
{
}
