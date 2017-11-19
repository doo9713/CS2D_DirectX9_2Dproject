#include "GameObjList.h"
#include "GameObj.h"

CGameObjList GAMEOBJ;

void CGameObjList::Update()
{
	for (auto obj = Active.begin(); obj != Active.end(); )
	{
		if ((*obj)->IsAlive)
		{
			(*obj)->Progress();
			++obj;
		}
		else
		{
			auto& taglist = TagList[(*obj)->Tag];
			for (auto remover = taglist.begin(); remover != taglist.end(); ++remover)
			{
				if (*remover == *obj)
				{
					taglist.erase(remover);
					break;
				}
			}
			auto& layerlist = LayerList[(*obj)->Layer];
			for (auto remover = layerlist.begin(); remover != layerlist.end(); ++remover)
			{
				if (*remover == *obj)
				{
					layerlist.erase(remover);
					break;
				}
			}

			delete *obj;
			obj = Active.erase(obj);
		}
	}
}

void CGameObjList::Render()
{
	for (auto Layer : LayerList)
	{
		for (auto obj : Layer)
		{
			obj->Rendering();
		}
	}
}

CGameObj* CGameObjList::AddGameObj(const char* name, TAG tag, LAYER layer)
{
	return AddGameObj(new CGameObj(name, tag, layer));
}

CGameObj* CGameObjList::AddGameObj(CGameObj* object)
{
	TagList[object->Tag].push_back(object);
	LayerList[object->Layer].push_back(object);
	Active.push_back(object);
	return object;
}

CGameObj* CGameObjList::FindGameObj(const char* name)
{
	for (auto obj : Active)
	{
		if (obj->Name == name)
			return obj;
	}
	return nullptr;
}

CGameObj* CGameObjList::FindGameObj(const char* name, TAG tag)
{
	for (auto obj : TagList[tag])
	{
		if (obj->Name == name)
			return obj;
	}
	return nullptr;
}

CGameObj* CGameObjList::FindGameObj(const char* name, LAYER layer)
{
	for (auto obj : LayerList[layer])
	{
		if (obj->Name == name)
			return obj;
	}
	return nullptr;
}

CGameObjList::CGameObjList()
{}

CGameObjList::~CGameObjList()
{
	for (auto obj : Active)
	{
		delete obj;
	}
	Active.clear();
}
