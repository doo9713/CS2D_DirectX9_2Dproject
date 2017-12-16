#include "LoadApp.h"
#include "GameObjList.h"
#include "GameObj.h"
#include "SpriteRender.h"
#include "AnimClipList.h"
#include "LoadManager.h"
#include "GameSound.hpp"

void CLoadApp::Initialize()
{
	GameSound Snd;
	Snd->Stop("Main");

	TEXTURE.Clear();
	GAMEOBJ.Clear();

	CGameObj* obj;
	CSpriteRender* csr;

	TEXTURE.Load("Loading", "../Resource/Texture/BackGround");
	TEXTURE.Load("Bar", "../Resource/Texture/Ui/");

	obj = GAMEOBJ.AddGameObj("LoadingManager", Tag_Manager, Layer_Background);
	obj->AddComponent<CLoadManager>();
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Loading";
	csr->Page = 1;

	gSceneCtrl = SCENE_LOADING;
}

CLoadApp::CLoadApp()
{
}

CLoadApp::~CLoadApp()
{
}
