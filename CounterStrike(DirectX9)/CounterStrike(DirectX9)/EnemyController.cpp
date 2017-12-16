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
#include "Animation.h"
#include "AutoGunItem.h"
#include "ShotGunItem.h"
#include "Rigid.h"
#include "GameSound.hpp"

RTTILINK(CEnemyController, CController)

int CEnemyController::EnemyCnt = 0;

void CEnemyController::Start()
{
	++EnemyCnt;

	/* 플레이어 게임 오브젝트를 찾는다 */
	Target = GAMEOBJ.FindGameObj("Player", Tag_Player);
	if (Target == nullptr)
		Destroy(this);

	Weapon = (WEAPON)Random(0, 1);

	/* 총 발사 이펙트 */
	auto eff = GAMEOBJ.AddGameObj("GunFireEffect", Tag_Effect, Layer_Effect);
	eff->AddComponent<CSpriteRender>();
	eff->Position = VECTOR3(26, -1, 0);
	eff->Parent = &gameObj;
	Anim = eff->AddComponent<CAnimation>();

	if (Weapon == Weapon_AutoGun)
		ActionTime = 0.15;
	else
		ActionTime = 1;

	Health = 100;
}

void CEnemyController::Update()
{
	/* 캐릭터 죽음 */
	if (Health == 0)
	{
		GameSound Snd;
		Snd->Play("Pain");

		for (int i = 0; i < 6; ++i)
			MakeBlood();
		int temp = Random(0, 9);
		if(temp < 2)
			MakeItem(Weapon);
		--EnemyCnt;
		Destroy(gameObj);
	}

	if ((Target->Position - gameObj.Position).Length() < ViewLength)
	{
		/* 일정거리에서 적이 플레이어를 바라보도록 설정 */
		if (rate == 0)
		{
			firstAngle = gameObj.Angle;
			dstAngle = ToTarget(Target->Position, gameObj.Position) + 180.0;
			if(dstAngle >= 360) dstAngle -= 360;
			if (firstAngle != dstAngle)
			{
				if (firstAngle > 180)
				{
					if (firstAngle - 180 > dstAngle)
						dstAngle += 360;
				}
				else if (firstAngle < 180)
				{
					if (firstAngle + 180 < dstAngle)
						dstAngle -= 360;
				}
			}
		}

		rate = Clamp(rate + TIME.Delta * 8, 0.0, 1.0);
		gameObj.Angle = Lerp(rate, firstAngle, dstAngle);

		if (dstAngle != ToTarget(Target->Position, gameObj.Position) + 180)
			rate = 0;

		/* 일정거리에서 적이 플레이어를 향해 총 발사 설정 */
		double CompareAngle = dstAngle - gameObj.Angle;
		if (CompareAngle <= 10 || CompareAngle >= 350)
		{		
			if (Weapon == Weapon_AutoGun)
			{
				Anim->AnimationName = "GunFireEffect";
				if (Time > ActionTime)
				{
					GameSound Snd;
					Snd->Play("AutoGun");
					//Snd->SetVolume(50);

					MakeBullet(Random(gameObj.Angle - 2, gameObj.Angle + 2));

					if (Time != 0)
						Time -= ActionTime;
				}
			}
			else
			{
				if (Time > ActionTime)
				{
					GameSound Snd;
					Snd->Play("ShotGun");
					//Snd->SetVolume(50);

					Anim->AnimationName = "GunFireEffect";
					AddInvoke(CF(ShotGunEffEnd), 0.2);
					for (int i = -3; i < 4; ++i)
					{
						MakeBullet(gameObj.Angle + i,
							Random(gameObj.Position.x - 10, gameObj.Position.x + 10),
							Random(gameObj.Position.y - 10, gameObj.Position.y + 10));
					}

					if (Time > ActionTime)
						Time -= ActionTime;
				}
			}
			Time += TIME.Delta;
		}

		/* 일정거리에서 적이 나를 향해 전진 */
		int t_Length;
		if (Weapon == Weapon_AutoGun) t_Length = 200;
		else t_Length = 100;
		if ((Target->Position - gameObj.Position).Length() > t_Length)
		{
			VECTOR3 Dir = VECTOR3(1, 0, 0);
			Dir.Rotation(gameObj.Angle);
			Dir.Normalize();
			gameObj.Position += Dir * TIME.Delta * 150;
		}
	}
	else
		Anim->AnimationName = "";
}

void CEnemyController::OnCollisionEnter(CGameObj* Other)
{
	if (!strcmp(Other->Name.data(), "Explosion"))
	{
		for (int i = 0; i < 6; ++i)
			MakeBlood();

		Health = Clamp(Health - 100, 0, 100);
	}

	if (Other->Tag == Tag_Ammo && (Other->GetComponent<CAmmo>()->Shooter)->Tag == Tag_Player)
	{
		for (int i = 0; i < 3; ++i)
			MakeBlood();

		Health = Clamp(Health - Random(15, 30), 0, 100);
		
		VECTOR3 shooterPos = (Other->GetComponent<CAmmo>()->Shooter)->Position;
		float distance = (gameObj.Position - shooterPos).Length();
		if (distance < 1000)
			ViewLength = distance + 200;
	}
}

CEnemyController::CEnemyController(CGameObj* Owner)
	: CController(Owner), Target(nullptr), ViewLength(320), rate(0), firstAngle(0), dstAngle(0)
{
}

CEnemyController::~CEnemyController()
{
}

void CEnemyController::MakeItem(WEAPON myWeapon)
{
	if (myWeapon > Weapon_ShotGun)
		return;

	auto obj = GAMEOBJ.AddGameObj("BulletItem", Tag_Item, Layer_EnviromentDown);
	obj->Position = gameObj.Position;
	obj->AddComponent<CRigid>();
	obj->AddComponent<CBoxCollider>();

	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Item";

	switch (myWeapon)
	{
	case Weapon_AutoGun :
		obj->AddComponent<CAutoGunItem>();
		csr->Page = 4;
		break;
	case Weapon_ShotGun :
		obj->AddComponent<CShotGunItem>();
		csr->Page = 5;
		break;
	}
}

void CEnemyController::ShotGunEffEnd()
{
	Anim->AnimationName = "";
}