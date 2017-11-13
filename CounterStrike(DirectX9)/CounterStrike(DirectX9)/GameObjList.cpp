#include "GameObjList.h"
#include "GameObj.h"

CGameObjList GAMEOBJ;

void CGameObjList::Update()
{
	for (auto object = Active.begin(); object != Active.end(); )
	{
		if ((*object)->IsAlive)
		{
			(*object)->Progress();
			++object;
		}
		else
		{
			auto& taglist = TagList[(*object)->Tag];
			for (auto remover = taglist.begin(); remover != taglist.end(); ++remover)
			{
				if (*remover == *object)
				{
					taglist.erase(remover);
					break;
				}
			}
			auto& layerlist = LayerList[(*object)->Layer];
			for (auto remover = layerlist.begin(); remover != layerlist.end(); ++remover)
			{
				if (*remover == *object)
				{
					layerlist.erase(remover);
					break;
				}
			}

			delete *object;
			object = Active.erase(object);
		}
	}
}

void CGameObjList::Render()
{
	for (auto Layer : LayerList)
	{
		for (auto object : Layer)
		{
			object->Rendering();
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

CGameObjList::CGameObjList()
{}

CGameObjList::~CGameObjList()
{
	for (auto object : Active)
	{
		delete object;
	}
	Active.clear();
}
