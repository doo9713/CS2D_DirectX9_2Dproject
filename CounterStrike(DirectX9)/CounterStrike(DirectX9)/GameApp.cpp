#include "GameApp.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "SpriteRender.h"
#include "BoxCollider.h"
#include "Rigid.h"
#include "Animation.h"
#include "AnimClipList.h"
#include "PlayerController.h"
#include "EnemyController.h"

void CGameApp::Initialize()
{
	DRX.Init(hWnd, false);
	FONT.Init();

	MATRIX Projection;
	D3DXMatrixOrthoLH(&Projection, ScreenWidth, ScreenHeight, 0, 1);
	DRX->SetTransform(D3DTS_PROJECTION, &Projection);

	// TODO : Game Initialize Code
	TEXTURE.Load("Player", "../Resource/Texture/Player");
	TEXTURE.Load("Box", "../Resource/Texture/Object/Box");
	TEXTURE.Load("Bullet", "../Resource/Texture/Bullet");
	TEXTURE.Load("GunFire", "../Resource/Texture/Effect/GunFire");
	TEXTURE.Load("BodyPart", "../Resource/Texture/BodyPart");
	TEXTURE.Load("Tree", "../Resource/Texture/Object/Tree");

	ANIMCLIP.OnLoad("GunFireEffect", "../Resource/AnimClip/GunFire.Clip");

	SHADER.OnLoad("Default", "../Resource/Effect/Default.fx");

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

	/* Temp make Box */
	obj = GAMEOBJ.AddGameObj("Box", Tag_Enviroment, Layer_EnviromentDown);
	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(50, 50);
	box->Freez = true;
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Box";
	obj->Position = VECTOR3(0, 100);
	obj->AddComponent<CRigid>();

	/* Temp make Tree */
	obj = GAMEOBJ.AddGameObj("Tree", Tag_Enviroment, Layer_EnviromentUp);
	obj->Position = VECTOR3(-100, 100);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Tree";

	/* Temp make Enemy */
	obj = GAMEOBJ.AddGameObj("Enemy", Tag_Enemy, Layer_Character);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CEnemyController>();
	obj->Center = VECTOR3(12, 0, 0);
	obj->Position = VECTOR3(300, 0);
	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 2;

	// TODO : UI Initialize Code
	TEXTURE.Load("Symbol", "../Resource/Texture/Ui/Symbol");
	TEXTURE.Load("Number", "../Resource/Texture/Ui/Number");
	TEXTURE.Load("Bar", "../Resource/Texture/Ui/");

	obj = GAMEOBJ.AddGameObj("Health", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-760, -420);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Symbol";
	csr->Page = 0;

	obj = GAMEOBJ.AddGameObj("Armor", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-620, -420);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Symbol";
	csr->Page = 1;

	obj = GAMEOBJ.AddGameObj("Timer", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(-100, -420);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Symbol";
	csr->Page = 2;
}

CGameApp::CGameApp()
{
}

CGameApp::~CGameApp()
{
}
