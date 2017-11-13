#include "Component.h"
#include "GameObj.h"

RTTIBASE(CComponent)

void CComponent::InvokeRun()
{
	for (auto invoke = InvokeData.begin(); invoke != InvokeData.end();)
	{
		if ((**invoke)())
		{
			delete *invoke;
			invoke = InvokeData.erase(invoke);
		}
		else ++invoke;
	}

	for (auto invoke : InvokeRepeatData)
		(*invoke.second)();
}

void CComponent::AddInvoke(function<void()> func, double delay)
{
	Invoke* invoke = new Invoke(delay, func);
	InvokeData.push_back(invoke);
}

void CComponent::AddInvoke(string key, function<void()> func, double delay, double repeat)
{
	Invoke* invoke = new InvokeRepeat(delay, func, repeat);
	InvokeRepeatData.insert(make_pair(key, invoke));
}

void CComponent::AddInvoke(string key, function<void()> func, function<bool()> events)
{
	Invoke* invoke = new InvokeEvent(func, events);
	InvokeRepeatData.insert(make_pair(key, invoke));
}

void CComponent::Destroy(CGameObj* obj)
{
	if (obj)
	{
		obj->IsAlive = false;
		if (obj->parent)
		{
			for (auto dst = obj->parent->child.begin();
				dst != obj->parent->child.end(); ++dst)
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

void CComponent::Destroy(CGameObj& obj)
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

CComponent::CComponent(CGameObj * Owner)
	: gameObj(*Owner), IsAlive(true)
{
}

CComponent::~CComponent()
{
	for (auto invoke : InvokeData)
	{
		delete invoke;
	}
	for (auto invoke : InvokeRepeatData)
	{
		delete invoke.second;
	}
	InvokeData.clear();
	InvokeRepeatData.clear();
}