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

	CGameObj* obj;
	CSpriteRender* csr;
	CBoxCollider* box;

#pragma region File Load
	// TODO : File Load Code
	TEXTURE.Load("Text", "../Resource/Texture/Text");
	TEXTURE.Load("BackGround", "../Resource/Texture/Map");
	TEXTURE.Load("Player", "../Resource/Texture/Player");
	TEXTURE.Load("Box", "../Resource/Texture/Object/Box");
	TEXTURE.Load("Ammo", "../Resource/Texture/Ammo");
	TEXTURE.Load("GunFire", "../Resource/Texture/Effect/GunFire");
	TEXTURE.Load("Explosion", "../Resource/Texture/Effect/Explosion");
	TEXTURE.Load("BodyPart", "../Resource/Texture/BodyPart");
	TEXTURE.Load("Tree", "../Resource/Texture/Object/Tree");
	TEXTURE.Load("Item", "../Resource/Texture/Object/Item"); // page : 0 -> C4, 1 -> Bag, 2 -> Armor, 3 -> Health, 4 -> AutoGun, 5 -> ShotGun

	ANIMCLIP.OnLoad("GunFireEffect", "../Resource/AnimClip/GunFire.Clip");
	ANIMCLIP.OnLoad("ExplosionEffect", "../Resource/AnimClip/Explosion.Clip");

	SHADER.OnLoad("Default", "../Resource/Effect/Default.fx");

	FONT.FontLoad("Default", 0, "../Resource/Font/Font_01.txt");
#pragma endregion

#pragma region Map obj Init
	/* Make BackGround */
	obj = GAMEOBJ.AddGameObj("BackGround", Tag_Enviroment, Layer_Background);
	obj->Position = VECTOR3(0, 0);
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "BackGround";

	/* Make Wall */
	MakeWall(0, 875, 3000, 50);
	MakeWall(0, -875, 3000, 50);
	MakeWall(1475, 0, 50, 1800);
	MakeWall(-1475, 0, 50, 1800);

	MakeTransWall(-1025, 725, 50, 350);
	MakeTransWall(-1250, 575, 500, 50);
	MakeTransWall(575, -675, 50, 400);
	MakeTransWall(1025, -475, 900, 50);

	/* Make Box*/
	MakeBox(175, 125);
	MakeBox(125, 125);
	MakeBox(175, 75);

	MakeBox(-125, 125);
	MakeBox(-75, 125);
	MakeBox(-125, 75);

	MakeBox(175, -175);
	MakeBox(125, -175);
	MakeBox(175, -125);

	MakeBox(-125, -175);
	MakeBox(-75, -175);
	MakeBox(-125, -125);

	MakeBox(-1425, 525, 3);
	MakeBox(-1375, 525, 3);
	MakeBox(-1300, 500, 4, 100, 100);

	MakeBox(-1250, 300, 4, 100, 100);
	MakeBox(-1175, 325, 3);
	MakeBox(-1300, 200, 4, 100, 100);
	MakeBox(-1250, 100, 4, 100, 100);
	MakeBox(-1175, 75, 3);

	MakeBox(-1275, -75, 6);
	MakeBox(-1225, -75, 6);
	MakeBox(-1300, -150, 7, 100, 100);
	MakeBox(-1200, -150, 7, 100, 100);
	MakeBox(-1275, -225, 6);
	MakeBox(-1225, -225, 6);
	MakeBox(-1275, -275, 6);
	MakeBox(-1275, -325, 6);
	MakeBox(-1275, -375, 6);
	MakeBox(-1225, -375, 6);
	MakeBox(-1175, -375, 6);

	MakeBox(-1275, -525, 6);
	MakeBox(-1325, -525, 6);
	MakeBox(-1375, -525, 6);
	MakeBox(-1425, -525, 6);

	MakeBox(-1375, -725, 2, 150, 150);

	MakeBox(150, 550, 4, 100, 100);
	MakeBox(-150, 800, 4, 100, 100);
	MakeBox(-175, 725, 3);
	MakeBox(250, 750, 4, 100, 100);

	MakeBox(1150, 800, 1, 100, 100);
	MakeBox(1225, 575, 2, 150, 150);
	MakeBox(1325, 525);
	MakeBox(1375, 525);
	MakeBox(1425, 525);

	MakeBox(1325, 175, 6);
	MakeBox(1375, 175, 6);
	MakeBox(1425, 175, 6);
	MakeBox(1275, 175, 6);
	MakeBox(1275, 125, 6);
	MakeBox(1275, 75, 6);

	MakeBox(1300, -200, 7, 100, 100);
	MakeBox(1400, -200, 7, 100, 100);

	MakeBox(-100, -700, 1, 100, 100);
	MakeBox(-175, -725);
	MakeBox(-225, -725);
	MakeBox(-275, -725);
	MakeBox(-275, -775);
	MakeBox(-275, -825);
	MakeBox(350, -800, 1, 100, 100);
	MakeBox(325, -725);
	MakeBox(275, -725);
	MakeBox(225, -725);
	MakeBox(175, -725);
	MakeBox(125, -725);

	/* Make Other Obj */
	MakeTree(-75, 75);
	MakeTree(-160, 580);
	MakeTree(-330, 190);
	MakeTree(-430, 790);
	MakeTree(-540, 590);
	MakeTree(-570, 700);
	MakeTree(-840, 120);
	MakeTree(-890, 590);
	MakeTree(-930, 647);
	MakeTree(-940, 260);
	MakeTree(-1030, 230);

	MakeTree(-260, -290);
	MakeTree(-400, -200);
	MakeTree(-480, -330);
#pragma endregion

#pragma region Character Obj Init
	// TODO : Game Initialize Code
	obj = GAMEOBJ.AddGameObj("Player", Tag_Player, Layer_Character);

	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);

	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 3;

	obj->Center = VECTOR3(12, 0, 0);
	obj->AddComponent<CPlayerController>();
	obj->AddComponent<CRigid>();
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

	//obj = GAMEOBJ.AddGameObj("Timer", Tag_UI, Layer_UI);
	//obj->Position = VECTOR3(-100, -420);
	//csr = obj->AddComponent<CSpriteRender>();
	//csr->RenderKey = "Symbol";
	//csr->Page = 2;
#pragma endregion

#pragma region Font
	FONT.WordScale = VECTOR3(1, 1);
	FONT.WordJump = 10;
	FONT.WordLine = 200;
#pragma endregion

#pragma region Test Code
	/* Temp make Enemy */
	obj = GAMEOBJ.AddGameObj("Enemy", Tag_Enemy, Layer_Character);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CEnemyController>();
	obj->Center = VECTOR3(12, 0, 0);
	obj->Position = VECTOR3(400, 0);
	obj->Angle = Random(0, 360);

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
	obj->Angle = Random(0, 360);

	box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);

	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Player";
	csr->Page = 3;

	/* Temp make Item */
	obj = GAMEOBJ.AddGameObj("HealthItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(300, 300);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CHealthItem>();
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 3;

	obj = GAMEOBJ.AddGameObj("ArmorItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(400, 300);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CArmorItem>();
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 2;

	obj = GAMEOBJ.AddGameObj("BulletItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(500, 300);
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

void CGameApp::MakeWall(float posx, float posy, float sizex, float sizey)
{
	auto obj = GAMEOBJ.AddGameObj("EndLineWall", Tag_Enviroment, Layer_Background);
	obj->Position = VECTOR3(posx, posy);
	obj->AddComponent<CRigid>();

	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(sizex, sizey);
	box->Freez = true;
}

void CGameApp::MakeWall(VECTOR3 pos, VECTOR3 size)
{
	
}

void CGameApp::MakeTransWall(float posx, float posy, float sizex, float sizey)
{
	auto obj = GAMEOBJ.AddGameObj("EndLineWall", Tag_Enviroment, Layer_Background);
	obj->Position = VECTOR3(posx, posy);

	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(sizex, sizey);
	box->Freez = true;
}

void CGameApp::MakeTransWall(VECTOR3 pos, VECTOR3 size)
{
	MakeTransWall(pos.x, pos.y, size.x, size.y);
}

void CGameApp::MakeBox(float posx, float posy, UINT page, float sizex, float sizey)
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

void CGameApp::MakeBox(VECTOR3 pos, UINT page, VECTOR3 size)
{
	MakeBox(pos.x, pos.y, page, size.x, size.y);
}

void CGameApp::MakeTree(float posx, float posy)
{
	auto obj = GAMEOBJ.AddGameObj("Tree", Tag_Enviroment, Layer_EnviromentUp);
	obj->Position = VECTOR3(posx, posy);
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Tree";
}

void CGameApp::MakeTree(VECTOR3 pos)
{
	MakeTree(pos.x, pos.y);
}
