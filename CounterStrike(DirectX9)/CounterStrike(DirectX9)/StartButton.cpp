#include "StartButton.h"
#include "GameObj.h"
#include "SpriteRender.h"

RTTILINK(CStartButton, CUIButton)

void CStartButton::Start()
{
	csr = gameObj.GetComponent<CSpriteRender>();
}

void CStartButton::OnButton()
{
	if (csr) csr->Page = 3;
}

void CStartButton::OutButton()
{
	if (csr) csr->Page = 2;
}

void CStartButton::ClickButton()
{
	gSceneCtrl = SCENE_LOAD;
}

CStartButton::CStartButton(CGameObj* Owner)
	: CUIButton(Owner)
{
}

CStartButton::~CStartButton()
{
}
