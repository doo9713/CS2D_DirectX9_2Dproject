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
	void MakeWall(float posx, float posy, float sizex = 50, float sizey = 50);
	void MakeWall(VECTOR3 pos, VECTOR3 size = VECTOR3(50, 50));
	void MakeTransWall(float posx, float posy, float sizex = 50, float sizey = 50);
	void MakeTransWall(VECTOR3 pos, VECTOR3 size = VECTOR3(50, 50));
	void MakeBox(float posx, float posy, UINT page = 0, float sizex = 50, float sizey = 50);
	void MakeBox(VECTOR3 pos, UINT page = 0, VECTOR3 size = VECTOR3(50, 50));
};

