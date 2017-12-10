#pragma once

#include "Component.h"

class CGameManger : public CComponent
{
	RTTICHECK
private :
	bool IsOver;
	string Str;
public :
	void Start();
	void Update();
	void Render();
public :
	CGameManger(CGameObj* Owner);
	~CGameManger();
};

