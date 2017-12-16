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
#include "GameManger.h"
#include "GameSound.hpp"

void CGameApp::Initialize()
{
	GameSound Snd;
	Snd->Play("Game");

	CGameObj* obj;
	CSpriteRender* csr;
	CBoxCollider* box;

#pragma region Map obj Init
	/* Make Game Manager */
	obj = GAMEOBJ.AddGameObj("GameManager", Tag_UI, Layer_UI);
	obj->AddComponent<CGameManger>();
	obj->Position = VECTOR3(-600, 100);

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

	/* Make Tree Obj */
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
	MakeTree(-890, -280);
	MakeTree(-960, -160);
	MakeTree(-1100, -360);
	MakeTree(-1200, -310);
	MakeTree(-490, -650);
	MakeTree(-740, -600);
	MakeTree(-770, -770);
	MakeTree(-1030, -680);

	MakeTree(240, 620);
	MakeTree(320, 540);
	MakeTree(390, 730);
	MakeTree(500, 600);
	MakeTree(480, 250);
	MakeTree(250, 140);
	MakeTree(910, 130);
	MakeTree(920, 420);
	MakeTree(1100, 350);
	MakeTree(1270, 400);
	MakeTree(1330, 260);

	MakeTree(180, -260);
	MakeTree(300, -600);
	MakeTree(360, -300);
	MakeTree(780, -280);
	MakeTree(960, -190);
	MakeTree(1170, -220);
	MakeTree(1320, -340);

	/* Make Other Obj */
	MakeTank(-200, 300, 50, 80);
	MakeTank(850, 570, 170, 130);
	MakeBoat(600, -550, 250);
	MakeBoat(760, -500, 2000);
#pragma endregion

#pragma region Character Obj Init
	// TODO : Make Player Code
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

	// TODO : Make Enemy Code
	CEnemyController::EnemyCnt = 0;
	MakeEnemy(-900, 300);
	MakeEnemy(-900, -270);
	MakeEnemy(-1400, 100);
	MakeEnemy(-1320, -50);
	MakeEnemy(50, 800);
	MakeEnemy(-40, 750);
	MakeEnemy(1300, 50);
	MakeEnemy(1440, -40);
	MakeEnemy(800, -420);
	MakeEnemy(650, -360);
	MakeEnemy(580, -420);
	MakeEnemy(-60, -800);
	MakeEnemy(50, -790);
	MakeEnemy(1350, 700);
	MakeEnemy(1280, 720);
	MakeEnemy(-500, 260);
	MakeEnemy(-440, 150);
	MakeEnemy(-840, 680);
	MakeEnemy(-890, 620);
	MakeEnemy(-890, -620);
	MakeEnemy(-750, -670);
	MakeEnemy(600, 300);
	MakeEnemy(540, 230);
	MakeEnemy(960, 500);
	MakeEnemy(940, 430);
#pragma endregion

#pragma region Item Obj Init
	MakeBulletItem(650, -420);
	MakeHealthItem(125, 75);
	MakeArmorItem(125, -125);
	MakeHealthItem(1300, 800);
	MakeArmorItem(1370, 790);
	MakeBulletItem(1340, 750);
	MakeHealthItem(-1350, 350);
	MakeArmorItem(-1400, -600);
#pragma endregion

#pragma region UI Init
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
#pragma endregion

	gSceneCtrl = SCENE_GAME;
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
	MakeWall(pos.x, pos.y, size.x, size.y);
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

void CGameApp::MakeBoat(float posx, float posy, float ang)
{
	auto obj = GAMEOBJ.AddGameObj("Boat", Tag_Enviroment, Layer_EnviromentDown);
	obj->Position = VECTOR3(posx, posy);
	obj->Angle = ang;
	obj->AddComponent<CRigid>();
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Vehicle";
	csr->Page = 2;
	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(80, 190);
	box->Freez = true;
}

void CGameApp::MakeBoat(VECTOR3 pos, float ang)
{
	MakeBoat(pos.x, pos.y, ang);
}

void CGameApp::MakeTank(float posx, float posy, float botang, float topang)
{
	auto obj = GAMEOBJ.AddGameObj("TankBottom", Tag_Enviroment, Layer_EnviromentDown);
	obj->Position = VECTOR3(posx, posy);
	obj->Angle = botang;
	obj->AddComponent<CRigid>();
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Vehicle";
	csr->Page = 0;
	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(90, 180);
	box->Freez = true;

	obj = GAMEOBJ.AddGameObj("TankTop", Tag_Enviroment, Layer_EnviromentUp);
	obj->Position = VECTOR3(posx, posy);
	obj->Angle = topang;
	csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Vehicle";
	csr->Page = 1;
}

void CGameApp::MakeTank(VECTOR3 pos, float botang, float topang)
{
	MakeTank(pos.x, pos.y, botang, topang);
}

void CGameApp::MakeEnemy(float posx, float posy)
{
	auto obj = GAMEOBJ.AddGameObj("Enemy", Tag_Enemy, Layer_Character);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CEnemyController>();
	obj->Center = VECTOR3(12, 0, 0);
	obj->Position = VECTOR3(posx, posy);
	obj->Angle = Random(0, 360);

	auto box = obj->AddComponent<CBoxCollider>();
	box->Size = VECTOR3(20, 20);
	box->Center = VECTOR3(-10, 0, 0);

	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Enemy";
}

void CGameApp::MakeEnemy(VECTOR3 pos)
{
	MakeEnemy(pos.x, pos.y);
}

void CGameApp::MakeBulletItem(float posx, float posy)
{
	auto obj = GAMEOBJ.AddGameObj("BulletItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(posx, posy);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CBulletItem>();
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 1;
}

void CGameApp::MakeBulletItem(VECTOR3 pos)
{
	MakeBulletItem(pos.x, pos.y);
}

void CGameApp::MakeArmorItem(float posx, float posy)
{
	auto obj = GAMEOBJ.AddGameObj("ArmorItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(posx, posy);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CArmorItem>();
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 2;
}

void CGameApp::MakeArmorItem(VECTOR3 pos)
{
	MakeArmorItem(pos.x, pos.y);
}


void CGameApp::MakeHealthItem(float posx, float posy)
{
	auto obj = GAMEOBJ.AddGameObj("HealthItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = VECTOR3(posx, posy);
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();
	obj->AddComponent<CHealthItem>();
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";
	csr->Page = 3;
}

void CGameApp::MakeHealthItem(VECTOR3 pos)
{
	MakeHealthItem(pos.x, pos.y);
}