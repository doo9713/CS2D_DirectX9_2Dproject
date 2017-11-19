#include "GameApp.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "SpriteRender.h"
#include "BoxCollider.h"
#include "Rigid.h"
#include "Animation.h"
#include "AnimClipList.h"
#include "GunFireEffect.h"
#include "PlayerController.h"
#include "EnemyController.h"

void CGameApp::Initialize()
{
	DRX.Init(hWnd, false);
	FONT.Init();

	MATRIX Projection;
	D3DXMatrixOrthoLH(&Projection, ScreenWidth, ScreenHeight, 0, 1);
	DRX->SetTransform(D3DTS_PROJECTION, &Projection);

	// TODO : Initialize Code
	TEXTURE.Load("Player", "../Resource/Texture/Player");
	TEXTURE.Load("Box", "../Resource/Texture/Object");
	TEXTURE.Load("Bullet", "../Resource/Texture/Bullet");
	TEXTURE.Load("GunFire", "../Resource/Texture/Effect/GunFire");

	ANIMCLIP.OnLoad("GunFireEffect", "../Resource/AnimClip/GunFire.Clip");

	auto obj = GAMEOBJ.AddGameObj("Player", Tag_Player, Layer_Character);
	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 3;
	obj->Center = VECTOR3(12, 0, 0);
	obj->AddComponent<CPlayerController>();
	obj->AddComponent<CRigid>();

	auto eff = GAMEOBJ.AddGameObj("GunFireEffect", Tag_Effect, Layer_Effect);
	eff->AddComponent<CSpriteRender>();
	eff->Position = VECTOR3(26, -1, 0);
	eff->Parent = obj;
	eff->AddComponent<CGunFireEffect>();
	auto anim = eff->AddComponent<CAnimation>();

	obj = GAMEOBJ.AddGameObj("Box", Tag_Enviroment, Layer_Enviroment);
	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(50, 50);
	box->Freez = true;
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Box";
	obj->Position = VECTOR3(0, 100);
	obj->AddComponent<CRigid>();

	/* Temp make Enemy */
	obj = GAMEOBJ.AddGameObj("Enemy", Tag_Enemy, Layer_Character);
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CRigid>();
	obj->AddComponent<CEnemyController>();
	obj->Center = VECTOR3(12, 0, 0);
	obj->Position = VECTOR3(300, 0);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 2;
}

CGameApp::CGameApp()
{
}

CGameApp::~CGameApp()
{
}
