#pragma once

#include "Component.h"

class CSpriteRender;
class CUIButton : public CComponent
{
	RTTICHECK
protected :
	CSpriteRender* csr;
public :
	VECTOR3 Center;
	VECTOR3 Size;
public :
	void Update();
public :
	CUIButton(CGameObj* Owner);
	~CUIButton();
};

