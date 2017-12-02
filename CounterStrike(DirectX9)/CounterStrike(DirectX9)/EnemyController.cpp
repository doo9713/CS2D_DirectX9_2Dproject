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
	auto obj = GAMEOBJ.AddGameObj("Bullet", Tag_Ammo, Layer_EnviromentDown);
	obj->Angle = gameObj.Angle + 45;
	obj->Position = gameObj.Position;
	obj->AddComponent<CBoxCollider>();

	auto bullet = obj->AddComponent<CBullet>();
	bullet->Dir = VECTOR3(1, 0, 0);
	bullet->Dir.Rotation(gameObj.Angle);
	bullet->Dir.Normalize();
	bullet->Shooter = &gameObj;

	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Ammo";
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

	/* 일정거리에서 적이 플래이어를 바라보도록 설정 */
	static double rate = 0;
	static double firstAngle = 0;
	static double dstAngle = 0;
	if ((Target->Position - gameObj.Position).Length() < ViewLength)
	{
		if (rate == 0)
		{
			firstAngle = gameObj.Angle;
			dstAngle = ToTarget(Target->Position, gameObj.Position) + 180;
			if (dstAngle >= 360) dstAngle -= 360;
			if (firstAngle < 90 && dstAngle > 270) firstAngle += 360;
			if (dstAngle < 90 && firstAngle > 270) dstAngle += 360;
		}

		rate = Clamp(rate + TIME.Delta * 8, 0.0, 1.0);
		gameObj.Angle = Lerp(rate, firstAngle, dstAngle);

		if (dstAngle != ToTarget(Target->Position, gameObj.Position) + 180)
		{
			firstAngle = gameObj.Angle;
			dstAngle = ToTarget(Target->Position, gameObj.Position) + 180;
			if (dstAngle >= 360) dstAngle -= 360;
			if (firstAngle < 90 && dstAngle > 270) firstAngle += 360;
			if (dstAngle < 90 && firstAngle > 270) dstAngle += 360;
			rate = 0;
		}
		//gameObj.Angle = ToTarget(Target->Position, gameObj.Position) + 180;
	}
}

void CEnemyController::OnCollisionEnter(CGameObj* Other)
{
	if (!strcmp(Other->Name.data(), "Explosion"))
	{
		for (int i = 0; i < 6; ++i)
		{
			auto obj = GAMEOBJ.AddGameObj("BodyPart", Tag_Enviroment, Layer_EnviromentDown);
			obj->Position.x = gameObj.Position.x - Random(-15, 15);
			obj->Position.y = gameObj.Position.y - Random(-15, 15);
			auto csr = obj->AddComponent<CSpriteRender>();
			csr->RenderKey = obj->Name;
			csr->Page = Random(0, 7);
		}

		Health = Clamp(Health - 100, 0, 100);
	}

	if (Other->Tag == Tag_Ammo && Other->GetComponent<CAmmo>()->Shooter != &gameObj)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto obj = GAMEOBJ.AddGameObj("BodyPart", Tag_Enviroment, Layer_EnviromentDown);
			obj->Position.x = gameObj.Position.x - Random(-15, 15);
			obj->Position.y = gameObj.Position.y - Random(-15, 15);
			auto csr = obj->AddComponent<CSpriteRender>();
			csr->RenderKey = obj->Name;
			csr->Page = Random(0, 7);
		}

		Health = Clamp(Health - Random(5, 15), 0, 100);
	}
}

CEnemyController::CEnemyController(CGameObj* Owner)
	: CController(Owner), Target(nullptr), ViewLength(300)
{
}

CEnemyController::~CEnemyController()
{
}
