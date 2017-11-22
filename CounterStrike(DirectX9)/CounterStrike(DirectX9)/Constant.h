#pragma once

class CGameObjList;
class CAnimClipList;

extern CGameObjList GAMEOBJ;
extern CAnimClipList ANIMCLIP;
extern HWND hWnd;

constexpr UINT ScreenWidth = 1600;
constexpr UINT ScreenHeight = 900;
constexpr double FrameTime = 0.01666666;

enum TAG
{
	Tag_Default,
	Tag_Player,
	Tag_Enemy,
	Tag_Bullet,
	Tag_Enviroment,
	Tag_Effect,
	Tag_UI,
	Tag_End
};

enum LAYER
{
	Layer_Default,
	Layer_Background,
	Layer_EnviromentDown,
	Layer_Character,
	Layer_Effect,
	Layer_EnviromentUp,
	Layer_UI,
	Layer_End
};