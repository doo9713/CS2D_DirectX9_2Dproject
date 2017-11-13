#include "GameObj.h"
#include "Component.h"
#include "GameObjList.h"

void CGameObj::_SetTag(TAG tag)
{
	auto& taglist = GAMEOBJ.TagList[this->tag];
	for (auto obj = taglist.begin(); obj != taglist.end(); ++obj)
	{
		if (*obj == this)
		{
			taglist.erase(obj);
			break;
		}
	}
	this->tag = tag;
	GAMEOBJ.TagList[tag].push_back(this);
}

void CGameObj::_SetLayer(LAYER layer)
{
	auto& layerlist = GAMEOBJ.LayerList[this->layer];
	for (auto obj = layerlist.begin(); obj != layerlist.end(); ++obj)
	{
		if (*obj == this)
		{
			layerlist.erase(obj);
			break;
		}
	}
	this->layer = layer;
	GAMEOBJ.LayerList[layer].push_back(this);
}

void CGameObj::_SetParent(CGameObj * parent)
{
	if (this->parent)
	{
		for (auto obj = this->parent->child.begin(); obj != this->parent->child.end(); ++obj)
		{
			if (*obj == this)
			{
				this->parent->child.erase(obj);
				break;
			}
		}
	}
	this->parent = parent;
	if (this->parent)
		this->parent->child.push_back(this);
}

void CGameObj::Progress()
{
	for (auto com = component.begin(); com != component.end(); )
	{
		if ((*com)->IsAlive)
		{
			(*com)->Update();
			(*com)->InvokeRun();
			++com;
		}
		else
		{
			delete *com;
			com = component.erase(com);
		}
	}
}

void CGameObj::Rendering()
{
	for (auto com : component)
		com->Render();
}

void CGameObj::Destroy(CComponent* com) 
{
	if (com) com->IsAlive = false;
}

void CGameObj::Destroy(CComponent& com) 
{
	com.IsAlive = false;
}

void CGameObj::Destroy(CGameObj* obj)
{
	if (obj)
	{
		obj->IsAlive = false;
		if (obj->parent)
		{
			for (auto dst = obj->parent->child.begin(); dst != obj->parent->child.end(); ++dst)
			{
				if (*dst == obj)
				{
					obj->parent->child.erase(dst);
					break;
				}
			}
		}

		for (auto dst : obj->child)
		{
			dst->parent = nullptr;
			Destroy(dst);
		}
	}
}

void CGameObj::Destroy(CGameObj& obj)
{
	obj.IsAlive = false;
	if (obj.parent)
	{
		for (auto dst = obj.parent->child.begin();
			dst != obj.parent->child.end(); ++dst)
		{
			if (*dst == &obj)
			{
				obj.parent->child.erase(dst);
				break;
			}
		}
	}

	for (auto dst : obj.child)
	{
		dst->parent = nullptr;
		Destroy(dst);
	}
}

bool CGameObj::SameParent(CGameObj * Other)
{
	CGameObj* My = this;
	while (My->parent) My = My->parent;
	while (Other->parent) Other = Other->parent;
	if (My == Other) return true;
	return false;
}

CGameObj::CGameObj(const char* name, TAG tag, LAYER layer)
	: Angle(0), Scale(1, 1, 1), name(name), tag(tag), layer(layer), IsAlive(true), parent(nullptr)
{
}

CGameObj::~CGameObj()
{
	for (auto com : component)
		delete com;
	component.clear();
}
