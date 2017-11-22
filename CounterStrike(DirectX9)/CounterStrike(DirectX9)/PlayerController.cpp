#include "PlayerController.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "BoxCollider.h"
#include "SpriteRender.h"
#include "Bullet.h"
#include "LeftMove.h"
#include "RightMove.h"
#include "UpMove.h"
#include "DownMove.h"
#include "Animation.h"

RTTILINK(CPlayerController, CController)

void CPlayerController::Start()
{
	Health = 100;
	Armor = 100;

	/* 총 발사 이펙트 */
	auto eff = GAMEOBJ.AddGameObj("GunFireEffect", Tag_Effect, Layer_Effect);
	eff->AddComponent<CSpriteRender>();
	eff->Position = VECTOR3(26, -1, 0);
	eff->Parent = &gameObj;
	Anim = eff->AddComponent<CAnimation>();

	/* 체력과 아머 UI */
	CGameObj* obj;
	for (int i = 0; i < 3; ++i)
	{
		obj = GAMEOBJ.AddGameObj("", Tag_UI, Layer_UI);
		obj->Position = HealthPos[i];
		HealthRender[i] = obj->AddComponent<CSpriteRender>();
		HealthRender[i]->RenderKey = "Number";
		HealthRender[i]->Page = PositionNum(i, Health);

		obj = GAMEOBJ.AddGameObj("", Tag_UI, Layer_UI);
		obj->Position = ArmorPos[i];
		ArmorRender[i] = obj->AddComponent<CSpriteRender>();
		ArmorRender[i]->RenderKey = "Number";
		ArmorRender[i]->Page = PositionNum(i, Armor);
	}

	/* 대기바 생성 */
	obj = GAMEOBJ.AddGameObj("BarBackGround", Tag_UI, Layer_UI);
	obj->Scale = VECTOR3(0.5, 0.3);
	obj->Position = VECTOR3(0, -25);
	WaitingBar[0] = obj->AddComponent<CSpriteRender>();
	WaitingBar[0]->RenderKey = "";
	WaitingBar[0]->ShaderKey = "Default";
	WaitingBar[0]->ChangeColorMul(100, 0, 0, 0);
	WaitingBar[0]->ChangeColorAddAfter(0, 140, 140, 140);

	obj = GAMEOBJ.AddGameObj("BarInside", Tag_UI, Layer_UI);
	obj->Scale = VECTOR3(0.49, 0.2);
	obj->Position = VECTOR3(0, -25);
	WaitingBar[1] = obj->AddComponent<CSpriteRender>();
	WaitingBar[1]->RenderKey = "";

	/* 총알 UI */
	for (int i = 0; i < 3; ++i)
	{
		obj = GAMEOBJ.AddGameObj("", Tag_UI, Layer_UI);
		obj->Position = TotalBulletPos[i];
		TotalBulletRender[i] = obj->AddComponent<CSpriteRender>();
		TotalBulletRender[i]->RenderKey = "Number";
		TotalBulletRender[i]->Page = PositionNum(i, TotalBullet[Weapon]);

		obj = GAMEOBJ.AddGameObj("", Tag_UI, Layer_UI);
		obj->Position = CurrentBulletPos[i];
		CurrentBulletRender[i] = obj->AddComponent<CSpriteRender>();
		CurrentBulletRender[i]->RenderKey = "Number";
		CurrentBulletRender[i]->Page = PositionNum(i, Bullet);
	}
	InvisibleNumber(TotalBulletRender, TotalBullet[Weapon]);
	InvisibleNumber(CurrentBulletRender, Bullet);
}

void CPlayerController::Update()
{
	/* 플래이어가 마우스 좌표를 바라봄 */
	VECTOR3 Mouse = GetMousePosition();
	MATRIX Matrix;
	DRX->GetTransform(D3DTS_VIEW, &Matrix);	// 게임 맵 전체 좌표 기준으로 맞춤
	Mouse.TransformCoord(Matrix);
	gameObj.Angle = Angle(Mouse - gameObj.Position);

	/* 움직임 시작 */
	if (KEY.Push('S'))
		gameObj.AddComponent<CDownMove>();
	if (KEY.Push('W'))
		gameObj.AddComponent<CUpMove>();
	if (KEY.Push('D'))
		gameObj.AddComponent<CRightMove>();
	if (KEY.Push('A'))
		gameObj.AddComponent<CLeftMove>();
	/* 움직임 종료 */
	if (KEY.Pull('S'))
		Destroy(gameObj.GetComponent<CDownMove>());
	if (KEY.Pull('W'))
		Destroy(gameObj.GetComponent<CUpMove>());
	if (KEY.Pull('D'))
		Destroy(gameObj.GetComponent<CRightMove>());
	if (KEY.Pull('A'))
		Destroy(gameObj.GetComponent<CLeftMove>());

	/* 총 교환 */
	if (KEY.Push('1'))
	{
		TotalBullet[Weapon] += Bullet;
		Weapon = Weapon_Change;
		AddInvoke(OCF(WeaponChange, Weapon_AutoGun), 1);
		ActionTime = 0.15;
	}
	if (KEY.Push('2'))
	{
		TotalBullet[Weapon] += Bullet;
		Weapon = Weapon_Change;
		AddInvoke(OCF(WeaponChange, Weapon_ShotGun), 1);
		ActionTime = 1;
	}

	/* 총 발사 */
	int i = -3;
	double Angle;
	CGameObj* obj;
	CBullet* bullet;
	CSpriteRender* csr;
	switch (Weapon)
	{
	case Weapon_AutoGun :
		if (KEY.Push(VK_LBUTTON))
			Time = 0;
		if (KEY.Down(VK_LBUTTON) && Bullet > 0 && !IsReloading)
		{
			Anim->AnimationName = "GunFireEffect";
			if (Time > ActionTime || Time == 0)
			{
				Angle = Random(gameObj.Angle - 2, gameObj.Angle + 2);
				obj = GAMEOBJ.AddGameObj("Bullet", Tag_Bullet, Layer_EnviromentDown);
				obj->Position = gameObj.Position;
				obj->Angle = Angle + 45;
				obj->AddComponent<CBoxCollider>();

				bullet = obj->AddComponent<CBullet>();
				bullet->Dir = VECTOR3(1, 0, 0);
				bullet->Dir.Rotation(Angle);
				bullet->Dir.Normalize();
				bullet->Shooter = &gameObj;

				csr = obj->AddComponent<CSpriteRender>();
				csr->RenderKey = "Bullet";

				if(Time != 0)
					Time -= ActionTime;
				Bullet = Clamp(Bullet - 1, 0, MagazineBullet[Weapon_AutoGun]);
				for (int i = 0; i < 3; ++i)
					CurrentBulletRender[i]->Page = PositionNum(i, Bullet);
				InvisibleNumber(CurrentBulletRender, Bullet);
				if (Bullet == 0)
					Anim->AnimationName = "";
			}
			Time += TIME.Delta;
		}
		if (KEY.Pull(VK_LBUTTON))
			Anim->AnimationName = "";
		break;
	case Weapon_ShotGun :
		if (KEY.Push(VK_LBUTTON) && Bullet > 0 && !IsReloading)
		{
			if (Time > ActionTime || Time == 0)
			{
				Anim->AnimationName = "GunFireEffect";
				AddInvoke(CF(ShotGunEffEnd), 0.2);
				for (; i < 4; ++i)
				{
					Angle = gameObj.Angle + i;
					obj = GAMEOBJ.AddGameObj("Bullet", Tag_Bullet, Layer_EnviromentDown);
					obj->Position.x = Random(gameObj.Position.x - 10, gameObj.Position.x + 10);
					obj->Position.y = Random(gameObj.Position.y - 10, gameObj.Position.y + 10);
					obj->Angle = Angle + 45;
					obj->AddComponent<CBoxCollider>();

					bullet = obj->AddComponent<CBullet>();
					bullet->Dir = VECTOR3(1, 0, 0);
					bullet->Dir.Rotation(Angle);
					bullet->Dir.Normalize();
					bullet->Shooter = &gameObj;

					csr = obj->AddComponent<CSpriteRender>();
					csr->RenderKey = "Bullet";
				}
				Bullet = Clamp(Bullet - 1, 0, MagazineBullet[Weapon_ShotGun]);
				for (int i = 0; i < 3; ++i)
					CurrentBulletRender[i]->Page = PositionNum(i, Bullet);
				InvisibleNumber(CurrentBulletRender, Bullet);
			}
			if (Time > ActionTime)
				Time = 0;
		}
		if (Time <= ActionTime)
			Time += TIME.Delta;
		break;
	}

	/* 총 장전 */
	if (KEY.Push('R'))
	{
		WaitingBar[0]->RenderKey = "Bar";
		WaitingBar[1]->RenderKey = "Bar";
		WaitingBar[1]->gameObj.Scale = VECTOR3(0, 0.2);

		IsReloading = true;
	}

	static double rate = 0;
	if (IsReloading)
	{
		rate = Clamp(rate + TIME.Delta * 0.7);
		WaitingBar[1]->gameObj.Scale = VECTOR3(Lerp(rate, 0.0, 0.49), 0.2);
		if (rate == 1)
		{
			WaitingBar[0]->RenderKey = "";
			WaitingBar[1]->RenderKey = "";
			rate = 0;
			
			UINT needBullet = MagazineBullet[Weapon] - Bullet;
			if (TotalBullet[Weapon] <= needBullet)
			{
				Bullet += TotalBullet[Weapon];
				TotalBullet[Weapon] = 0;
			}
			else
			{
				TotalBullet[Weapon] -= needBullet;
				Bullet += needBullet;
			}

			for (int i = 0; i < 3; ++i)
			{
				TotalBulletRender[i]->Page = PositionNum(i, TotalBullet[Weapon]);
				CurrentBulletRender[i]->Page = PositionNum(i, Bullet);
			}
			InvisibleNumber(TotalBulletRender, TotalBullet[Weapon]);
			InvisibleNumber(CurrentBulletRender, Bullet);

			IsReloading = false;
		}
	}
}

void CPlayerController::OnCollisionEnter(CGameObj * Other)
{
	if (Other->Tag == Tag_Bullet && Other->GetComponent<CBullet>()->Shooter != &gameObj)
	{
		auto obj = GAMEOBJ.AddGameObj("BodyPart", Tag_Enviroment, Layer_EnviromentDown);
		obj->Position = gameObj.Position;
		auto csr = obj->AddComponent<CSpriteRender>();
		csr->RenderKey = obj->Name;
		csr->Page = Random(0, 7);

		if (Armor > 0)
		{
			Armor = Clamp(Armor - Random(2, 4), 0, 100);
			Health = Clamp(Health - Random(0, 2), 0, 100);

			for (int i = 0; i < 3; ++i)
			{
				HealthRender[i]->Page = PositionNum(i, Health);
				ArmorRender[i]->Page = PositionNum(i, Armor);
			}
		}
		else
		{
			Health = Clamp(Health - Random(5, 8), 0, 100);
			for (int i = 0; i < 3; ++i)
				HealthRender[i]->Page = PositionNum(i, Health);
		}

		InvisibleNumber(HealthRender, Health);
		InvisibleNumber(ArmorRender, Armor);
	}
}

CPlayerController::CPlayerController(CGameObj* Owner)
	: CController(Owner), Time(0), ActionTime(1), Weapon(Weapon_ShotGun), Anim(nullptr), Health(100), Armor(100), IsReloading(false)
{
	HealthPos[0] = VECTOR3(-670, -420);
	HealthPos[1] = VECTOR3(-700, -420);
	HealthPos[2] = VECTOR3(-730, -420);
	ArmorPos[0] = VECTOR3(-530, -420);
	ArmorPos[1] = VECTOR3(-560, -420);
	ArmorPos[2] = VECTOR3(-590, -420);
	TotalBulletPos[0] = VECTOR3(730, -420);
	TotalBulletPos[1] = VECTOR3(700, -420);
	TotalBulletPos[2] = VECTOR3(670, -420);
	CurrentBulletPos[0] = VECTOR3(630, -420);
	CurrentBulletPos[1] = VECTOR3(600, -420);
	CurrentBulletPos[2] = VECTOR3(570, -420);

	TotalBullet = new UINT(Weapon_Change);
	MagazineBullet = new UINT(Weapon_Change);

	TotalBullet[Weapon_AutoGun] = 270;
	TotalBullet[Weapon_ShotGun] = 45;
	MagazineBullet[Weapon_AutoGun] = 30;
	MagazineBullet[Weapon_ShotGun] = 5;
	Bullet = MagazineBullet[Weapon];
}

CPlayerController::~CPlayerController()
{
}

void CPlayerController::WeaponChange(WEAPON change)
{
	Weapon = change;

	UINT needBullet = MagazineBullet[Weapon];
	if (TotalBullet[Weapon] <= needBullet)
	{
		Bullet += TotalBullet[Weapon];
		TotalBullet[Weapon] = 0;
	}
	else
	{
		TotalBullet[Weapon] -= needBullet;
		Bullet = needBullet;
	}
	
	for (int i = 0; i < 3; ++i)
	{
		TotalBulletRender[i]->Page = PositionNum(i, TotalBullet[Weapon]);
		CurrentBulletRender[i]->Page = PositionNum(i, Bullet);
	}
	InvisibleNumber(TotalBulletRender, TotalBullet[Weapon]);
	InvisibleNumber(CurrentBulletRender, Bullet);
}

void CPlayerController::ShotGunEffEnd()
{
	Anim->AnimationName = "";
}

void CPlayerController::InvisibleNumber(CSpriteRender* src[3], UINT data)
{
	for (int i = 0; i < 3; ++i)
		src[i]->RenderKey = "Number";
	if (data < 100)
		src[2]->RenderKey = "";
	if (data < 10)
		src[1]->RenderKey = "";
}

UINT CPlayerController::PositionNum(UINT Position, UINT Data)
{
	// Position 0 : 0의자리 1 : 10의자리 100 : 100의자리
	switch (Position)
	{
	case 0 :
		return Data % 10;
	case 1 :
		if (Data > 100)
			Data -= (Data / 100) * 100;
		if (Data < 100) return Data / 10;
		else return 0;
	case 2 :
		if (Data > 100) return Data / 100;
		else if (Data < 100) return 0;
		else return 1;
	}
}
