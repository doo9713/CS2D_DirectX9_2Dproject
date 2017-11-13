#pragma once

#include "Defines.h"

class CApp
{
public :
	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Render();
public :
	CApp();
	~CApp();
};

