#pragma once

#include "Component.h"

class CSpriteRender;
class CEffectEvent : public CComponent
{
	RTTICHECK
protected :
	UINT lastPage;
	CSpriteRender* CSR;
public :
	bool IsLoop;
public :
	CEffectEvent(CGameObj* Owner);
	~CEffectEvent();
};

