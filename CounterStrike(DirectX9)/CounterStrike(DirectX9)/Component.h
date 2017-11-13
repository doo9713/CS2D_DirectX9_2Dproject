#pragma once

#include "Defines.h"

class CGameObj;
class CComponent
{
	RTTICHECK
private :
	bool IsAlive;
	list<Invoke*> InvokeData;
	map<string, Invoke*> InvokeRepeatData;
	void InvokeRun();
public :
	CGameObj& gameObj;
public :
	void AddInvoke(function<void()> func, double delay);
	void AddInvoke(string key, function<void()> func, double delay, double repeat);
	void AddInvoke(string key, function<void()> func, function<bool()> events);
public :
	template<typename T>
	T* GetComponent(UINT Cnt = 0)
	{
		return gameObj.GetComponent<T>(Cnt);
	}
	void Destroy(CGameObj* obj);
	void Destroy(CGameObj& obj);
	void Destroy(CComponent* com)
	{
		if (com) com->IsAlive = false;
	}
	void Destroy(CComponent& com)
	{
		com.IsAlive = false;
	}
public :
	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void OnButton() {}
	virtual void OnCollisionEnter(CGameObj* Other) {}
	virtual void OnCollisionStay(CGameObj* Other) {}
	virtual void OnCollisionExit(CGameObj* Other) {}
public :
	CComponent(CGameObj* Owner);
	CComponent(const CComponent&) = delete;
	virtual ~CComponent();

	friend class CGameObj;
};

