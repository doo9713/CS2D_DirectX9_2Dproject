#include "LoadManager.h"
#include "AnimClipList.h"
#include "GameObjList.h"
#include "GameObj.h"
#include "SpriteRender.h"

RTTILINK(CLoadManager, CComponent)

void CLoadManager::Start()
{
	/* 대기바 생성 */
	auto obj = GAMEOBJ.AddGameObj("BarBackGround", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(0, -400);
	obj->Scale = VECTOR3(1.03, 1.2);
	obj->Parent = &gameObj;
	LoadingBar[0] = obj->AddComponent<CSpriteRender>();
	LoadingBar[0]->RenderKey = "Bar";
	LoadingBar[0]->ShaderKey = "Default";
	LoadingBar[0]->ChangeColorMul(100, 0, 0, 0);
	LoadingBar[0]->ChangeColorAddAfter(0, 140, 140, 140);

	obj = GAMEOBJ.AddGameObj("BarInside", Tag_UI, Layer_UI);
	obj->Position = VECTOR3(0, -400);
	obj->Parent = &gameObj;
	LoadingBar[1] = obj->AddComponent<CSpriteRender>();
	LoadingBar[1]->RenderKey = "Bar";
}

void CLoadManager::Update()
{
	rate = LoadOrder / 16;
	LoadingBar[1]->gameObj.Scale = VECTOR3(Clamp(rate, 0.0, 1.0), 1);
	if (LoadOrder == 0)
	{
		TEXTURE.Load("Text", "../Resource/Texture/Text");
		++LoadOrder;
	}
	else if(LoadOrder == 1)
	{
		TEXTURE.Load("BackGround", "../Resource/Texture/Map");
		++LoadOrder;
	}
	else if (LoadOrder == 2)
	{
		TEXTURE.Load("Player", "../Resource/Texture/Player");
		++LoadOrder;
	}
	else if (LoadOrder == 3)
	{
		TEXTURE.Load("Enemy", "../Resource/Texture/Enemy");
		++LoadOrder;
	}
	else if (LoadOrder == 4)
	{
		TEXTURE.Load("Box", "../Resource/Texture/Object/Box");
		++LoadOrder;
	}
	else if (LoadOrder == 5)
	{
		TEXTURE.Load("Ammo", "../Resource/Texture/Ammo");
		++LoadOrder;
	}
	else if (LoadOrder == 6)
	{
		TEXTURE.Load("GunFire", "../Resource/Texture/Effect/GunFire");
		++LoadOrder;
	}
	else if (LoadOrder == 7)
	{
		TEXTURE.Load("Explosion", "../Resource/Texture/Effect/Explosion");
		++LoadOrder;
	}
	else if (LoadOrder == 8)
	{
		TEXTURE.Load("BodyPart", "../Resource/Texture/BodyPart");
		++LoadOrder;
	}
	else if (LoadOrder == 9)
	{
		TEXTURE.Load("Tree", "../Resource/Texture/Object/Tree");
		++LoadOrder;
	}
	else if (LoadOrder == 10)
	{
		TEXTURE.Load("Vehicle", "../Resource/Texture/Object/Vehicle");
		++LoadOrder;
	}
	else if (LoadOrder == 11)
	{
		TEXTURE.Load("Item", "../Resource/Texture/Object/Item"); // page : 0 -> C4, 1 -> Bag, 2 -> Armor, 3 -> Health, 4 -> AutoGun, 5 -> ShotGun
		++LoadOrder;
	}
	else if (LoadOrder == 12)
	{
		ANIMCLIP.OnLoad("GunFireEffect", "../Resource/AnimClip/GunFire.Clip");
		++LoadOrder;
	}
	else if (LoadOrder == 13)
	{
		ANIMCLIP.OnLoad("ExplosionEffect", "../Resource/AnimClip/Explosion.Clip");
		++LoadOrder;
	}
	else if (LoadOrder == 14)
	{
		TEXTURE.Load("Symbol", "../Resource/Texture/Ui/Symbol");
		++LoadOrder;
	}
	else if (LoadOrder == 15)
	{
		TEXTURE.Load("Number", "../Resource/Texture/Ui/Number");
		++LoadOrder;
	}
	else
	{
		if (KEY.Push(VK_SPACE))
		{
			gSceneCtrl = SCENE_LOADEND;
			Destroy(gameObj);
		}
	}
}

CLoadManager::CLoadManager(CGameObj* Owner)
	: CComponent(Owner), rate(0), LoadOrder(0)
{
	LoadingBar[0] = nullptr;
	LoadingBar[1] = nullptr;
}

CLoadManager::~CLoadManager()
{
}
