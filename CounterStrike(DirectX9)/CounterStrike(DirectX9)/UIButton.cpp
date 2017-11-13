#include "UIButton.h"
#include "GameObj.h"

RTTILINK(CUIButton, CComponent)

void CUIButton::Start()
{
	auto dst = gameObj.GetComponent<CUIButton>();
	if (dst != this) Destroy(this);
}

void CUIButton::Update()
{
	auto World = gameObj.World.Inverse();
	VECTOR3 Mouse = GetMousePosition() - Center;
	Mouse.TransformCoord(World);

	if (Mouse.x < Size.x * 0.5 && Mouse.x > Size.x * -0.5 && Mouse.y < Size.y * 0.5 && Mouse.y > Size.y * -0.5)
	{
		for (auto com : gameObj.component)
			com->OnButton();
	}
}

CUIButton::CUIButton(CGameObj* Owner)
	: CComponent(Owner)
{
}


CUIButton::~CUIButton()
{
}
