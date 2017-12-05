#include "GameApp.h"
#include "MenuApp.h"

HWND hWnd;

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
	wcex.hIcon = LoadIcon(Inst, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "CoiunterStrike2D";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
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
	CGameApp Game;
	CMenuApp Menu;
	//Game.Initialize();
	Menu.Initialize();

	while (true)
	{
		TimeC.SetTimer();
		FTime += TimeC.RealTime;
		UTime += TimeC.RealTime;
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (UTime > UpdateTime)
		{
			UTime -= UpdateTime;
			// TODO : App Update Code
			//Game.Update();
			Menu.Update();
		}

		if (FTime > FrameTime)
		{
			FTime -= FrameTime;
			// TODO : App Render Code
			//Game.Render();
			Menu.Render();
		}
	}

	return (int)msg.wParam;
}