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
	void MakeBox(float posx, float posy, float sizex, float sizey, UINT page = 0);
	void MakeBox(VECTOR3 pos, VECTOR3 size, UINT page = 0);
};

