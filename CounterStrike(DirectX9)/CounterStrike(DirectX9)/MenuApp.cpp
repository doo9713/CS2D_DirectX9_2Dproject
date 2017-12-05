#include "MenuApp.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "SpriteRender.h"
#include "UIButton.h"

void CMenuApp::Initialize()
{
	DRX.Init(hWnd, false);

	MATRIX Projection;
	D3DXMatrixOrthoLH(&Projection, ScreenWidth, ScreenHeight, 0, 1);
	DRX->SetTransform(D3DTS_PROJECTION, &Projection);

	CGameObj* obj;
	CSpriteRender* csr;
	CUIButton* bt;

#pragma region File Load
	// TODO : File Load Code
	TEXTURE.Load("BackGround", "../Resource/Texture/BackGround");
	TEXTURE.Load("Menu", "../Resource/Texture/Menu");
	TEXTURE.Load("Title", "../Resource/Texture/Title");

	SHADER.OnLoad("Default", "../Resource/Effect/Default.fx");
#pragma endregion

#pragma region Menu Init
	// TODO : Menu Initialize
	obj = GAMEOBJ.AddGameObj("BackGround", Tag_Default, Layer_Background);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "BackGround";

	obj = GAMEOBJ.AddGameObj("Title", Tag_Default, Layer_Background);
	obj->Position = VECTOR3(-300, 300);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Title";
	csr->ShaderKey = "Default";
	csr->ChangeColorMul(225, 0, 0, 0);
	csr->ChangeColorAddAfter(0, 225, 225, 0);

	obj = GAMEOBJ.AddGameObj("btStart", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-650, -50);
	obj->Scale = VECTOR3(2, 2);
	bt = obj->AddComponent<CUIButton>();
	bt->Size = VECTOR3(120, 35);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Menu";
	csr->Page = 2;

	obj = GAMEOBJ.AddGameObj("btQuit", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-650, -150);
	obj->Scale = VECTOR3(2, 2);
	bt = obj->AddComponent<CUIButton>();
	bt->Size = VECTOR3(120, 35);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Menu";
	csr->Page = 0;
#pragma  endregion
}

CMenuApp::CMenuApp()
{
}

CMenuApp::~CMenuApp()
{
}
