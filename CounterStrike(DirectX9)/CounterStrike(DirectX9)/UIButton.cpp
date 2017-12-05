#include "UIButton.h"
#include "GameObj.h"
#include "SpriteRender.h"

RTTILINK(CUIButton, CComponent)

void CUIButton::Start()
{
	auto dst = gameObj.GetComponent<CUIButton>();
	if (dst != this) Destroy(this);
}

void CUIButton::Update()
{
	auto World = gameObj.World.Inverse();
	VECTOR3 Mouse = GetMousePosition();
	Mouse.TransformCoord(World);

	if (Mouse.x < Size.x * 0.5 && Mouse.x > Size.x * -0.5 && Mouse.y < Size.y * 0.5 && Mouse.y > Size.y * -0.5)
	{
		for (auto com : gameObj.component)
			com->OnButton();

		if (KEY.Push(VK_LBUTTON))
		{

		}
	}
	else
	{
		if (gameObj.GetComponent<CSpriteRender>()->Page == 1)
			gameObj.GetComponent<CSpriteRender>()->Page = 0;
		if (gameObj.GetComponent<CSpriteRender>()->Page == 3)
			gameObj.GetComponent<CSpriteRender>()->Page = 2;
	}
}

void CUIButton::OnButton()
{
	if (gameObj.GetComponent<CSpriteRender>()->Page == 0)
		gameObj.GetComponent<CSpriteRender>()->Page = 1;
	if (gameObj.GetComponent<CSpriteRender>()->Page == 2)
		gameObj.GetComponent<CSpriteRender>()->Page = 3;
}

CUIButton::CUIButton(CGameObj* Owner)
	: CComponent(Owner)
{
}


CUIButton::~CUIButton()
{
}
