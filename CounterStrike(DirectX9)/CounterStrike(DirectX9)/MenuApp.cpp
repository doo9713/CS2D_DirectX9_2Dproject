#include "MenuApp.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "SpriteRender.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "GameSound.hpp"

void CMenuApp::Initialize()
{
	if (gSceneCtrl == SCENE_GAMEOVER)
	{
		TEXTURE.Clear();
		GAMEOBJ.Clear();

		DRX.Camera(0, 0);
	}	
	else
	{
		DRX.Init(hWnd, false);
		FONT.Init();

		MATRIX Projection;
		D3DXMatrixOrthoLH(&Projection, ScreenWidth, ScreenHeight, 0, 1);
		DRX->SetTransform(D3DTS_PROJECTION, &Projection);
	}

	GameSound Snd;
	Snd->Init(500);
	Snd->LoadSound("Main", "../Resource/Sound/Main.mp3", true);
	Snd->LoadSound("BtInto", "../Resource/Sound/btInto.mp3", false);
	Snd->LoadSound("BtClick", "../Resource/Sound/btClick.mp3", false);
	Snd->Play("Main");
	Snd->SetVolume(50);

	CGameObj* obj;
	CSpriteRender* csr;
	CUIButton* bt;

#pragma region File Load
	// TODO : File Load Code
	TEXTURE.Load("Text", "../Resource/Texture/Text");
	TEXTURE.Load("BackGround", "../Resource/Texture/BackGround");
	TEXTURE.Load("Menu", "../Resource/Texture/Menu");
	TEXTURE.Load("Title", "../Resource/Texture/Title");

	if (gSceneCtrl == SCENE_START)
	{
		SHADER.OnLoad("Default", "../Resource/Effect/Default.fx");
		FONT.FontLoad("Default", 0, "../Resource/Font/Font_01.txt");
	}	
#pragma endregion

#pragma region Menu Init
	// TODO : Menu Initialize
	obj = GAMEOBJ.AddGameObj("BackGround", Tag_Default, Layer_Background);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "BackGround";

	obj = GAMEOBJ.AddGameObj("Title", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-300, 300);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Title";
	csr->ShaderKey = "Default";
	csr->ChangeColorMul(225, 0, 0, 0);
	csr->ChangeColorAddAfter(0, 225, 225, 0);

	obj = GAMEOBJ.AddGameObj("btStart", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-650, -50);
	obj->Scale = VECTOR3(2, 2);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Menu";
	csr->Page = 2;
	bt = obj->AddComponent<CStartButton>();
	bt->Size = VECTOR3(120, 35);

	obj = GAMEOBJ.AddGameObj("btQuit", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-650, -150);
	obj->Scale = VECTOR3(2, 2);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Menu";
	csr->Page = 0;
	bt = obj->AddComponent<CExitButton>();
	bt->Size = VECTOR3(120, 35);
#pragma  endregion

	gSceneCtrl = SCENE_MAIN;
}

CMenuApp::CMenuApp()
{
}

CMenuApp::~CMenuApp()
{
}
