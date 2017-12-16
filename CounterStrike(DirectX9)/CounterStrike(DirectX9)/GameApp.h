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
	void MakeWall(VECTOR3 pos = VECTOR3(0, 0), VECTOR3 size = VECTOR3(50, 50));
	void MakeTransWall(float posx, float posy, float sizex = 50, float sizey = 50);
	void MakeTransWall(VECTOR3 pos = VECTOR3(0, 0), VECTOR3 size = VECTOR3(50, 50));
	void MakeBox(float posx, float posy, UINT page = 0, float sizex = 50, float sizey = 50);
	void MakeBox(VECTOR3 pos, UINT page = 0, VECTOR3 size = VECTOR3(50, 50));
	void MakeTree(float posx, float posy);
	void MakeTree(VECTOR3 pos);
	void MakeBoat(float posx, float posy, float ang = 0);
	void MakeBoat(VECTOR3 pos, float ang = 0);
	void MakeTank(float posx, float posy, float botang = 0, float topang = 0);
	void MakeTank(VECTOR3 pos, float botang, float topang = 0);
	void MakeEnemy(float posx, float posy);
	void MakeEnemy(VECTOR3 pos);
	void MakeBulletItem(float posx, float posy);
	void MakeBulletItem(VECTOR3 pos);
	void MakeArmorItem(float posx, float posy);
	void MakeArmorItem(VECTOR3 pos);
	void MakeHealthItem(float posx, float posy);
	void MakeHealthItem(VECTOR3 pos);
};

