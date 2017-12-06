#include "ExitButton.h"
#include "GameObj.h"
#include "SpriteRender.h"

RTTILINK(CExitButton, CUIButton)

void CExitButton::Start()
{
	csr = gameObj.GetComponent<CSpriteRender>();
}

void CExitButton::OnButton()
{
	if (csr) csr->Page = 1;
}

void CExitButton::OutButton()
{
	if (csr) csr->Page = 0;
}

void CExitButton::ClickButton()
{
	gSceneCtrl = SCENE_EXIT;
}

CExitButton::CExitButton(CGameObj* Owner)
	: CUIButton(Owner)
{
}

CExitButton::~CExitButton()
{
}
