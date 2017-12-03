#pragma once

#include "Controller.h"

//class CAnimation;
class CSpriteRender;
class CPlayerController : public CController
{
	RTTICHECK
private :
	bool IsReloading;
	CSpriteRender* WaitingBar[2]; // 0 -> ¹è°æ, 1 -> ¹Ù
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
	_declspec(property(get = _GetArmor, put = _SetArmor)) UINT ARMOR;
	const UINT _GetArmor() const { return Armor; }
	void _SetArmor(UINT armor) { Armor = armor; }
public :
	void Start();
	void Update();
	void OnCollisionEnter(CGameObj* Other);
public :
	CPlayerController(CGameObj* Owner);
	~CPlayerController();
public :
	void AddBullet();
	void InvalidateUI();
private :
	void WeaponChange(WEAPON change);
	void ShotGunEffEnd();
	void InvisibleNumber(CSpriteRender* src[3], UINT data);
	UINT PositionNum(UINT Position, UINT Data);
};

