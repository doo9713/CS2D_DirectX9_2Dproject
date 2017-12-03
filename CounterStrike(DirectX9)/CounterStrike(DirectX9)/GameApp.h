#pragma once

#include "App.h"

class CGameApp : public CApp
{
public :
	void Initialize();
public :
	CGameApp();
	~CGameApp();
private :
	void MakeBox(float posx, float posy, float sizex = 50, float sizey = 50, UINT page = 0);
	void MakeBox(VECTOR3 pos, VECTOR3 size = VECTOR3(50, 50), UINT page = 0);
};

