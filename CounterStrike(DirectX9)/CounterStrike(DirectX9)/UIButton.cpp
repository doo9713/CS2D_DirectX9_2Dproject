#include "UIButton.h"
#include "GameObj.h"
#include "GameSound.hpp"

RTTILINK(CUIButton, CComponent)

void CUIButton::Update()
{
	auto World = gameObj.World.Inverse();
	VECTOR3 Mouse = GetMousePosition();
	Mouse.TransformCoord(World);

	if (Mouse.x < Size.x * 0.5 && Mouse.x > Size.x * -0.5 && Mouse.y < Size.y * 0.5 && Mouse.y > Size.y * -0.5)
	{
		if (!CursorIn)
		{
			GameSound Snd;
			Snd->Play("BtInto");
			CursorIn = true;
		}

		for (auto com : gameObj.component)
			com->OnButton();

		if (KEY.Push(VK_LBUTTON))
		{
			for (auto com : gameObj.component)
			{
				GameSound Snd;
				Snd->Play("BtClick");
				com->ClickButton();
			}
		}
	}
	else
	{
		if (CursorIn)
			CursorIn = false;
		for (auto com : gameObj.component)
			com->OutButton();
	}
}

CUIButton::CUIButton(CGameObj* Owner)
	: CComponent(Owner), csr(nullptr), CursorIn(false)
{
}


CUIButton::~CUIButton()
{
}
