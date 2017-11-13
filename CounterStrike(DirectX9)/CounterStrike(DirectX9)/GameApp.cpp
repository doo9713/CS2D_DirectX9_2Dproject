#include "GameApp.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "Move.h"
#include "SpriteRender.h"

void CGameApp::Initialize()
{
	DRX.Init(hWnd, false);
	FONT.Init();

	MATRIX Projection;
	D3DXMatrixOrthoLH(&Projection, ScreenWidth, ScreenHeight, 0, 1);
	DRX->SetTransform(D3DTS_PROJECTION, &Projection);

	// TODO : Initialize Code
	TEXTURE.Load("Player", "../Resource/Texture/Player");

	auto obj = GAMEOBJ.AddGameObj("Player", Tag_Player, Layer_Character);
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 0;
	obj->AddComponent<CMove>();
}

CGameApp::CGameApp()
{
}

CGameApp::~CGameApp()
{
}
