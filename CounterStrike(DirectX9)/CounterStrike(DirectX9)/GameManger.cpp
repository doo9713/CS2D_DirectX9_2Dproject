#include "GameManger.h"
#include "GameObj.h"
#include "EnemyController.h"
#include "PlayerController.h"
#include "GameSound.hpp"

RTTILINK(CGameManger, CComponent)

void CGameManger::Start()
{
	FONT.WordScale = VECTOR3(4, 4);
	FONT.WordJump = 10;
}

void CGameManger::Update()
{
	if (CEnemyController::EnemyCnt <= 0)
	{
		Str = "You Win!!";
		IsOver = true;
	}
	else if (!CPlayerController::Alive)
	{
		Str = "You Lose!!";
		IsOver = true;
	}

	if (IsOver && KEY.Push(VK_SPACE))
	{
		GameSound Snd;
		Snd->Stop("Game");
		Snd->Close();

		gSceneCtrl = SCENE_GAMEOVER;
	}
}

void CGameManger::Render()
{
	if (IsOver)
	{
		MATRIX mat;
		DRX->GetTransform(D3DTS_VIEW, &mat);
		VECTOR3 Pos;
		Pos.x = gameObj.Position.x - mat._41;
		Pos.y = gameObj.Position.y - mat._42;
		FONT.Draw(Str.data(), "Default", Pos);
	}
}

CGameManger::CGameManger(CGameObj* Owner)
	: CComponent(Owner), Str(""), IsOver(false)
{
}

CGameManger::~CGameManger()
{
}
