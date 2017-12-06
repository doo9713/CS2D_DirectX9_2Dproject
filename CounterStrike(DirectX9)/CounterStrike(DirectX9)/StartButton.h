#pragma once

#include "UIButton.h"

class CStartButton : public CUIButton
{
	RTTICHECK
public :
	void Start();
	void OnButton();
	void OutButton();
	void ClickButton();
public :
	CStartButton(CGameObj* Owner);
	~CStartButton();
};

