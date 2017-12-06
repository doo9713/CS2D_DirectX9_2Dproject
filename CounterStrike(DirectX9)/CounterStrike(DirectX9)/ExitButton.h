#pragma once

#include "UIButton.h"

class CExitButton : public CUIButton
{
	RTTICHECK
public :
	void Start();
	void OnButton();
	void OutButton();
	void ClickButton();
public :
	CExitButton(CGameObj* Owner);
	~CExitButton();
};

