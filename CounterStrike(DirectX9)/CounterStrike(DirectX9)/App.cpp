#include "App.h"
#include "GameObjList.h"

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
}

CApp::CApp()
{
}

CApp::~CApp()
{
}
