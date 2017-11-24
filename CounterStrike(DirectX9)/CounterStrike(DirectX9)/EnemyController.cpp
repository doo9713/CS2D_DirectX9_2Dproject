#include "EnemyController.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "UpMove.h"
#include "DownMove.h"
#include "LeftMove.h"
#include "RightMove.h"
#include "Bullet.h"
#include "SpriteRender.h"
#include "BoxCollider.h"

RTTILINK(CEnemyController, CController)

void CEnemyController::Change()
{
	static bool check = true;
	if (check)
	{
		ChangeA();
		check = false;
	}
	else
	{
		ChangeB();
		check = true;
	}
}

void CEnemyController::ChangeA()
{
	gameObj.AddComponent<CRightMove>();
	Destroy(gameObj.GetComponent<CLeftMove>());
}

void CEnemyController::ChangeB()
{
	gameObj.AddComponent<CLeftMove>();
	Destroy(gameObj.GetComponent<CRightMove>());
}

void CEnemyController::Shoot()
{
	auto obj = GAMEOBJ.AddGameObj("Bullet", Tag_Bullet, Layer_EnviromentDown);
	obj->Angle = gameObj.Angle + 45;
	obj->Position = gameObj.Position;
	obj->AddComponent<CBoxCollider>();

	auto bullet = obj->AddComponent<CBullet>();
	bullet->Dir = VECTOR3(1, 0, 0);
	bullet->Dir.Rotation(gameObj.Angle);
	bullet->Dir.Normalize();
	bullet->Shooter = &gameObj;

	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Bullet";
}

void CEnemyController::Start()
{
	// 플레이어 게임 오브젝트를 찾는다
	Target = GAMEOBJ.FindGameObj("Player", Tag_Player);
	if (Target == nullptr)
		Destroy(this);

	Health = 100;

	/* Test Code */
	gameObj.AddComponent<CLeftMove>();
	AddInvoke("LeftRight", CF(Change), 1, 1);
	AddInvoke("Shoot", CF(Shoot), 0, 1);
}

void CEnemyController::Update()
{
	if (Health == 0)
		Destroy(gameObj);

	if ((Target->Position - gameObj.Position).Length() < 150)
	{
		gameObj.Angle = ToTarget(Target->Position, gameObj.Position) + 180;
	}
}

void CEnemyController::OnCollisionEnter(CGameObj* Other)
{
	if (Other->Tag == Tag_Bullet && Other->GetComponent<CBullet>()->Shooter != &gameObj)
	{
		auto obj = GAMEOBJ.AddGameObj("BodyPart", Tag_Enviroment, Layer_EnviromentDown);
		obj->Position = gameObj.Position;
		auto csr = obj->AddComponent<CSpriteRender>();
		csr->RenderKey = obj->Name;
		csr->Page = Random(0, 7);

		Health = Clamp(Health - Random(5, 15), 0, 100);
	}
}

CEnemyController::CEnemyController(CGameObj* Owner)
	: CController(Owner), Target(nullptr)
{
}

CEnemyController::~CEnemyController()
{
}
