#pragma once

#include "Component.h"

class CUIButton : public CComponent
{
	RTTICHECK
public :
	VECTOR3 Center;
	VECTOR3 Size;
public :
	void Start();
	void Update();
public :
	CUIButton(CGameObj* Owner);
	~CUIButton();
};
