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
#include "HealthItem.h"
#include "ArmorItem.h"
#include "BulletItem.h"

void CGameApp::Initialize()
{
	DRX.Init(hWnd, false);
	FONT.Init();

	MATRIX Projection;
	D3DXMatrixOrthoLH(&Projection, ScreenWidth, ScreenHeight, 0, 1);
	DRX->SetTransform(D3DTS_PROJECTION, &Projection);

#pragma region File Load
	// TODO : File Load Code
	TEXTURE.Load("BackGround", "../Resource/Temp/");
	TEXTURE.Load("Player", "../Resource/Texture/Player");
	TEXTURE.Load("Box", "../Resource/Texture/Object/Box");
	TEXTURE.Load("Ammo", "../Resource/Texture/Ammo");
	TEXTURE.Load("GunFire", "../Resource/Texture/Effect/GunFire");
	TEXTURE.Load("Explosion", "../Resource/Texture/Effect/Explosion");
	TEXTURE.Load("BodyPart", "../Resource/Texture/BodyPart");
	TEXTURE.Load("Tree", "../Resource/Texture/Object/Tree");
	TEXTURE.Load("Item", "../Resource/Texture/Object/Item"); // page : 0 -> C4, 1 -> Bag, 2 -> Armor, 3 -> Health

	ANIMCLIP.OnLoad("GunFireEffect", "../Resource/AnimClip/GunFire.Clip");
	ANIMCLIP.OnLoad("ExplosionEffect", "../Resource/AnimClip/Explosion.Clip");

	SHADER.OnLoad("Default", "../Resource/Effect/Default.fx");
#pragma endregion

#pragma region Obj Init
	// TODO : Game Initialize Code
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

	MakeBox(150, 150);
	MakeBox(100, 150);
	MakeBox(150, 100);

	MakeBox(-150, 150);
	MakeBox(-100, 150);
	MakeBox(-150, 100);

	MakeBox(150, -150);
	MakeBox(100, -150);
	MakeBox(150, -100);

	MakeBox(-150, -150);
	MakeBox(-100, -150);
	MakeBox(-150, -100);
#pragma endregion

#pragma region UI Init
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
#pragma endregion

#pragma region Test Code
	/* Temp make BackGround */
	obj = GAMEOBJ.AddGameObj("BackGround", Tag_Enviroment, Layer_Background);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "BackGround";

	/* Temp make Box */
	MakeBox(0, 500, 1800, 50, 1);
	MakeBox(0, -500, 1800, 50, 1);

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
	obj->Position = VECTOR3(400, 0);

	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);

	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 3;

	obj = GAMEOBJ.AddGameObj("Enemy", Tag_Enemy, Layer_Character);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CEnemyController>();
	obj->Center = VECTOR3(12, 0, 0);
	obj->Position = VECTOR3(-400, 0);

	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);

	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 3;

	/* Temp make Item */
	obj = GAMEOBJ.AddGameObj("HealthItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(-300, 300);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CHealthItem>();
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 3;

	obj = GAMEOBJ.AddGameObj("ArmorItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(-400, 300);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CArmorItem>();
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 2;

	obj = GAMEOBJ.AddGameObj("BulletItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(-500, 300);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CBulletItem>();
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 1;
#pragma endregion
}

CGameApp::CGameApp()
{
}

CGameApp::~CGameApp()
{
}

void CGameApp::MakeBox(float posx, float posy, float sizex, float sizey, UINT page)
{
	auto obj = GAMEOBJ.AddGameObj("Box", Tag_Enviroment, Layer_EnviromentDown);
	obj->Position = VECTOR3(posx, posy);
	obj->AddComponent<CRigid>();
	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(sizex, sizey);
	box->Freez = true;
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Box";
	csr->Page = page;
}

void CGameApp::MakeBox(VECTOR3 pos, VECTOR3 size, UINT page)
{
	MakeBox(pos.x, pos.y, size.x, size.y, page);
}
