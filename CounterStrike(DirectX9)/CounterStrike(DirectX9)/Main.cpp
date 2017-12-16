#include "GameApp.h"
#include "MenuApp.h"
#include "LoadApp.h"
#include "resource.h"

HWND hWnd;
SCENE gSceneCtrl;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE PrevInst,
	LPSTR CmdLine, int Show)
{
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Inst;
	wcex.hIcon = LoadIcon(Inst, IDI_CSICON);
	wcex.hCursor = LoadCursorFromFile("../Resource/ETC/mouse.cur");
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "CoiunterStrike2D";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_CSICON);
	RegisterClassExA(&wcex);

	RECT rc = { 0, 0, ScreenWidth, ScreenHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	hWnd = CreateWindowA("CoiunterStrike2D", "CS2D",
		WS_OVERLAPPEDWINDOW,
		50, 50,
		rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, Inst, nullptr);

	ShowWindow(hWnd, Show);
	UpdateWindow(hWnd);

	MSG msg;

	TimeClass TimeC;
	double FTime = 0;
	double UTime = 0;

	// TODO : App Initialize Code
	gSceneCtrl = SCENE_START;
	CMenuApp Menu;
	CLoadApp Load;
	CGameApp Game;

	while (true)
	{
		TimeC.SetTimer();
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (UTime > UpdateTime || UTime == 0)
		{
			UTime -= UpdateTime;
			// TODO : App Update Code
			switch (gSceneCtrl)
			{
			case SCENE_START :
				Menu.Initialize();
			case SCENE_MAIN :
				Menu.Update();
				break;
			case SCENE_LOADSTART :
				Load.Initialize();
			case SCENE_LOADING :
				Load.Update();
				break;
			case SCENE_LOADEND :
				Game.Initialize();
			case SCENE_GAME :
				Game.Update();
				break;
			case SCENE_GAMEOVER :
				Menu.Initialize();
				break;
			case SCENE_EXIT :
				return (int)msg.wParam;;
			default :
				break;
			}
		}

		if (FTime > FrameTime || FTime == 0)
		{
			FTime -= FrameTime;
			// TODO : App Render Code
			switch (gSceneCtrl)
			{
			case SCENE_MAIN:
				Menu.Render();
				break;
			case SCENE_LOADING:
				Load.Render();
				break;
			case SCENE_GAME:
				Game.Render();
				break;
			case SCENE_EXIT:
				return (int)msg.wParam;;
			default:
				break;
			}
		}
		FTime += TimeC.RealTime;
		UTime += TimeC.RealTime;
	}

	return (int)msg.wParam;
}