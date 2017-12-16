#include "App.h"
#include "GameObjList.h"
#include "GameSound.hpp"

void CApp::Update()
{
	KEY.Set();
	TIME.SetTimer();
	GAMEOBJ.Update();
}

void CApp::Render()
{
	DRX.Begin();
	GAMEOBJ.Render();
	DRX.End();

	GameSound Snd;
	Snd->Update();
}

CApp::CApp()
{
}

CApp::~CApp()
{
}
