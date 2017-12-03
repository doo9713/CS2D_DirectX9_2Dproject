#include "Controller.h"
#include "GameObj.h"
#include "GameObjList.h"
#include "BoxCollider.h"
#include "Bullet.h"
#include "SpriteRender.h"

RTTILINK(CController, CComponent)

CController::CController(CGameObj* Owner)
	: CComponent(Owner), Health(100), ActionTime(0), Time(0), Weapon(Weapon_AutoGun), Anim(nullptr)
{
}

CController::~CController()
{
}

void CController::MakeBullet(double angle)
{
	double Angle = angle;
	auto obj = GAMEOBJ.AddGameObj("Bullet", Tag_Ammo, Layer_EnviromentDown);
	obj->Position = gameObj.Position;
	obj->Angle = Angle + 45;
	obj->AddComponent<CBoxCollider>();

	auto bullet = obj->AddComponent<CBullet>();
	bullet->Dir = VECTOR3(1, 0, 0);
	bullet->Dir.Rotation(Angle);
	bullet->Dir.Normalize();
	bullet->Shooter = &gameObj;

	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Ammo";
}

void CController::MakeBullet(double angle, float posx, float posy)
{
	double Angle = gameObj.Angle;
	auto obj = GAMEOBJ.AddGameObj("Bullet", Tag_Ammo, Layer_EnviromentDown);
	obj->Position.x = posx;
	obj->Position.y = posy;
	obj->Angle = Angle + 45;
	obj->AddComponent<CBoxCollider>();

	auto bullet = obj->AddComponent<CBullet>();
	bullet->Dir = VECTOR3(1, 0, 0);
	bullet->Dir.Rotation(Angle);
	bullet->Dir.Normalize();
	bullet->Shooter = &gameObj;

	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = "Ammo";
}

void CController::MakeBlood()
{
	auto obj = GAMEOBJ.AddGameObj("BodyPart", Tag_Enviroment, Layer_EnviromentDown);
	obj->Position.x = gameObj.Position.x - Random(-15, 15);
	obj->Position.y = gameObj.Position.y - Random(-15, 15);
	auto csr = obj->AddComponent<CSpriteRender>();
	csr->RenderKey = obj->Name;
	csr->Page = Random(0, 7);
}