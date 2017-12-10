#pragma once

#include "Component.h"

class CSpriteRender;
class CLoadManager : public CComponent
{
	RTTICHECK
private :
	double rate;
	UINT LoadOrder;
	CSpriteRender* LoadingBar[2];
public :
	void Start();
	void Update();
public :
	CLoadManager(CGameObj* Owner);
	~CLoadManager();
};

