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

RTTILINK(CEnemyController, CController)

void CEnemyController::Start()
{
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
	if (Health == 0)
		Destroy(gameObj);

	if ((Target->Position - gameObj.Position).Length() < ViewLength)
	{
		/* 일정거리에서 적이 플레이어를 바라보도록 설정 */
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

		/* 일정거리에서 적이 플레이어를 향해 총 발사 설정 */
		double CompareAngle = dstAngle - gameObj.Angle;
		if (CompareAngle <= 10 || CompareAngle >= 350)
		{		
			if (Weapon == Weapon_AutoGun)
			{
				Anim->AnimationName = "GunFireEffect";
				if (Time > ActionTime || Time == 0)
				{
					MakeBullet(Random(gameObj.Angle - 2, gameObj.Angle + 2));

					if (Time != 0)
						Time -= ActionTime;
				}
			}
			else
			{
				if (Time > ActionTime || Time == 0)
				{
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
		VECTOR3 Dir = VECTOR3(1, 0, 0);
		Dir.Rotation(gameObj.Angle);
		Dir.Normalize();
		gameObj.Position += Dir * TIME.Delta * 200;
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

	if (Other->Tag == Tag_Ammo && Other->GetComponent<CAmmo>()->Shooter != &gameObj)
	{
		for (int i = 0; i < 3; ++i)
			MakeBlood();

		Health = Clamp(Health - Random(5, 15), 0, 100);
	}
}

CEnemyController::CEnemyController(CGameObj* Owner)
	: CController(Owner), Target(nullptr), ViewLength(320), rate(0), firstAngle(0), dstAngle(0)
{
}

CEnemyController::~CEnemyController()
{
}

void CEnemyController::ShotGunEffEnd()
{
	Anim->AnimationName = "";
}