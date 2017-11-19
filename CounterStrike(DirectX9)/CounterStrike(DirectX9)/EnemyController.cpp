#include "EnemyController.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "UpMove.h"
#include "DownMove.h"
#include "LeftMove.h"
#include "RightMove.h"

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

void CEnemyController::Start()
{
	// 플레이어 게임 오브젝트를 찾는다
	Target = GAMEOBJ.FindGameObj("Player", Tag_Player);
	if (Target == nullptr)
		Destroy(this);
	gameObj.AddComponent<CLeftMove>();
	AddInvoke("LeftRight", CF(Change), 1, 1);
}

void CEnemyController::Update()
{
	if ((Target->Position - gameObj.Position).Length() < 150)
	{
		gameObj.Angle = ToTarget(Target->Position, gameObj.Position) + 180;
	}
}

CEnemyController::CEnemyController(CGameObj* Owner)
	: CController(Owner), Target(nullptr)
{
}

CEnemyController::~CEnemyController()
{
}
