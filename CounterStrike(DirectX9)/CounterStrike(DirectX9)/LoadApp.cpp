#include "LoadApp.h"
#include "GameObjList.h"
#include "AnimClipList.h"

void CLoadApp::Initialize()
{
	GAMEOBJ.Clear();
	TEXTURE.Clear();

	TEXTURE.Load("Text", "../Resource/Texture/Text");
	TEXTURE.Load("BackGround", "../Resource/Texture/Map");
	TEXTURE.Load("Player", "../Resource/Texture/Player");
	TEXTURE.Load("Enemy", "../Resource/Texture/Enemy");
	TEXTURE.Load("Box", "../Resource/Texture/Object/Box");
	TEXTURE.Load("Ammo", "../Resource/Texture/Ammo");
	TEXTURE.Load("GunFire", "../Resource/Texture/Effect/GunFire");
	TEXTURE.Load("Explosion", "../Resource/Texture/Effect/Explosion");
	TEXTURE.Load("BodyPart", "../Resource/Texture/BodyPart");
	TEXTURE.Load("Tree", "../Resource/Texture/Object/Tree");
	TEXTURE.Load("Vehicle", "../Resource/Texture/Object/Vehicle");
	TEXTURE.Load("Item", "../Resource/Texture/Object/Item"); // page : 0 -> C4, 1 -> Bag, 2 -> Armor, 3 -> Health, 4 -> AutoGun, 5 -> ShotGun

	ANIMCLIP.OnLoad("GunFireEffect", "../Resource/AnimClip/GunFire.Clip");
	ANIMCLIP.OnLoad("ExplosionEffect", "../Resource/AnimClip/Explosion.Clip");

	gSceneCtrl = SCENE_GAME;
}

CLoadApp::CLoadApp()
{
}

CLoadApp::~CLoadApp()
{
}
