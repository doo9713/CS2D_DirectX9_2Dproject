#pragma once

#include "Defines.h"

class CComponent;
class CGameObjList;
class CUIButton;
class CRigid;
class CGameObj
{
private :
	bool IsAlive;
	string name;
	TAG tag;
	LAYER layer;
	CGameObj* parent;
	list<CComponent*> component;
	list<CGameObj*> child;
public :
	VECTOR3 Center;
	VECTOR3 Position;
	VECTOR3 Scale;
	FLOAT Angle;
public :
	_declspec(property(get = _GetName, put = _SetName)) string Name;
	_declspec(property(get = _GetTag, put = _SetTag)) TAG Tag;
	_declspec(property(get = _GetLayer, put = _SetLayer)) LAYER Layer;
	_declspec(property(get = _GetParent, put = _SetParent)) CGameObj* Parent;
	_declspec(property(get = _GetWorld)) MATRIX World;
public :
	const string& _GetName() const { return name; }
	const TAG& _GetTag() const { return tag; }
	const LAYER& _GetLayer() const { return layer; }
	CGameObj* _GetParent() { return parent; }
	MATRIX _GetWorld() const
	{
		MATRIX mAngle, mPosition, mScale, mCenter, mAround;
		mCenter.Move(Center);
		mScale.Scale(Scale);
		mPosition.Move(Position);
		mAngle.Rotation(Angle);
		if (parent)
			return mCenter * mScale * mAngle * mPosition * parent->World;
		return mCenter * mScale * mAngle * mPosition;
	}
public :
	void _SetName(string name) 
	{ 
		if (name != "") this->name = name; 
	}
	void _SetTag(TAG tag);
	void _SetLayer(LAYER layer);
	void _SetParent(CGameObj* parent);
public :
	void Progress();
	void Rendering();
public :
	void Destroy(CComponent* com);
	void Destroy(CComponent& com);
	void Destroy(CGameObj* obj);
	void Destroy(CGameObj& obj);
public :
	template <typename Type>
	Type* GetComponent(unsigned int Count = 0)
	{
		Type* result = nullptr;
		for (auto com : component)
		{
			if (com->GetRTTI().TreeIn(Type::_rtti))
			{
				result = (Type*)com;
				if (!Count)
					break;
				--Count;
			}
		}
		return result;
	}
	template <typename Type>
	Type* AddComponent()
	{
		Type* result = new Type(this);
		component.emplace_back(result);
		result->Start();
		return result;
	}
	bool SameParent(CGameObj* Other);
public :
	CGameObj(const char* _name = "GameObject", TAG _tag = TAG::Tag_Default, LAYER _layer = LAYER::Layer_Default);
	~CGameObj();

	friend class CComponent;
	friend class CGameObjList;
	friend class CUIButton;
	friend class CRigid;
};
