#pragma once

class CGameObjList;

extern CGameObjList GAMEOBJ;
extern HWND hWnd;

constexpr UINT ScreenWidth = 1600;
constexpr UINT ScreenHeight = 900;
constexpr double FrameTime = 0.01666666;

enum TAG
{
	Tag_Default,
	Tag_Player,
	Tag_Enemy,
	Tag_Enviroment,
	Tag_End
};

enum LAYER
{
	Layer_Default,
	Layer_Background,
	Layer_Enviroment,
	Layer_Character,
	Layer_Effect,
	Layer_UI,
	Layer_End
};