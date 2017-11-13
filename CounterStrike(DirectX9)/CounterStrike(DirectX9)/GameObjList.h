#pragma once

#include "Defines.h"

class CGameObj;
class CGameObjList
{
private :
	list<CGameObj*> TagList[Tag_End];
	list<CGameObj*> LayerList[Layer_End];
	list<CGameObj*> Active;
public :
	list<CGameObj*>& GetTag(TAG Tag) { return TagList[Tag]; }
	list<CGameObj*>& GetLayer(LAYER Layer) { return LayerList[Layer]; }
	list<CGameObj*>& GetActive() { return Active; }
public :
	void Update();
	void Render();
public :
	CGameObj* AddGameObj(const char* name = "GameObj", TAG tag = Tag_Default, LAYER layer = Layer_Default);
	CGameObj* AddGameObj(CGameObj* obj);
public :
	CGameObjList();
	CGameObjList(const CGameObjList&) = delete;
	~CGameObjList();

	friend class CGameObj;
};