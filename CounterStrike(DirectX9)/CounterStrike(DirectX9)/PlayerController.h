#pragma once

#include "Controller.h"

class CAnimation;
class CSpriteRender;
class CPlayerController : public CController
{
	RTTICHECK
private :
	enum WEAPON
	{
		Weapon_AutoGun,
		Weapon_ShotGun,
		Weapon_Change,
		Weapon_End
	};
	bool IsReloading;
	double ActionTime;
	double Time;
	WEAPON Weapon;
	CAnimation* Anim;
	CSpriteRender* WaitingBar[2]; // 0 -> ���, 1 -> ��
	UINT Health;
	UINT Armor;
	UINT Bullet;
	UINT* TotalBullet;
	UINT* MagazineBullet;
	CSpriteRender* HealthRender[3];
	CSpriteRender* ArmorRender[3];
	CSpriteRender* TotalBulletRender[3];
	CSpriteRender* CurrentBulletRender[3];
	VECTOR3 HealthPos[3];
	VECTOR3 ArmorPos[3];
	VECTOR3 TotalBulletPos[3];
	VECTOR3 CurrentBulletPos[3];
public :
	void Start();
	void Update();
	void OnCollisionEnter(CGameObj* Other);
public :
	CPlayerController(CGameObj* Owner);
	~CPlayerController();
private :
	void WeaponChange(WEAPON change);
	void ShotGunEffEnd();
	void InvisibleNumber(CSpriteRender* src[3], UINT data);
	UINT PositionNum(UINT Position, UINT Data);
};

