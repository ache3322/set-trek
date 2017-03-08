/*
* PROJECT		: SETTrek
* FILE			: main.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/01
* DESCRIPTION	: The main entry point for the game.
*/
#include <Windows.h>
#include "Graphics.h"
#include "GameManager.h"
#include "EffectManager.h"
#include "Level.h"
#include "Level1.h"
#include "Level2.h"


//-GLOBAL VARIABLES
Graphics* graphics;
volatile bool isResize;


//-FUNCTION PROTOTYPES
HWND initWindow(HINSTANCE hInstance, int nCmd);


/**
* \brief This is for handling any Window events.
* \details Note - The Window Process must be defined before Main.
* \param hwnd - HWND - A window handle to the client window
* \param uMsg - UINT - The window message descriptor
* \param wParam - WPARAM - HI-WORD of the window message
* \param lParam - LPARAM - LO-WORD of the window message (has additional information about message)
* \return LRESULT : A LONG type of the message.
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_DESTROY message - destroying the Window
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	if (uMsg == WM_SIZE)
	{
		//WORD hi = HIWORD(lParam);
		//WORD lo = LOWORD(lParam);
		//isResize = true;
		//graphics->Resize(hwnd);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



/**
* \brief The wWinMain is the main entry point for the application.
* \param hInstance - HINSTANCE - The handle instance to the client window
* \param prevInstance - HINSTANCE - The previous handle instance to a window
* \param cmd - LPWSTR - The command line arguments
* \param nCmdShow - int - Describes how the Window will be shown
* \return int : The return for main
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	// Initialize the Main Window
	HWND windowHandle = initWindow(hInstance, nCmdShow);
	if (!windowHandle)
		return -1;

	// Get the actual size of the game window
	RECT windowSize;
	GetClientRect(windowHandle, &windowSize);

	// Initialize the Graphics object
	graphics = new Graphics();
	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		// An error occurred whilst initializing the graphics
		return -1;
	}

	// Initialize the GameLevel (ensures Graphics object is known for all Levels)
	Level::Init(graphics);
	EffectManager::Init(graphics);

	// Initialize the GameManager
	GameManager::Init();
	// Load the initial level
	GameManager::LoadLevel(new Level2(), D2D1::RectF(0, 0, (FLOAT)windowSize.right, (FLOAT)windowSize.bottom));

	// Now show/display the window
	ShowWindow(windowHandle, nCmdShow);


	/* GAMP LOOP */

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
			// Process input

			// Update the game - any values, assets, coordinates, sizes
			GameManager::Update();

			// Rendering...
			graphics->BeginDraw();
			// Render the Game
			GameManager::Render();
			graphics->EndDraw();
		}
	}

	GameManager::UnloadLevel();
	delete graphics;
	return 0;
}


/*
* \brief Initialize the main window.
* \param hInstance - HINSTANCE - The handle instance of the client
* \param nCmd - int - Describes how the Window will be shown
* \return HWND : A handle to the window.
*/
HWND initWindow(HINSTANCE hInstance, int nCmd)
{
	/* WNDCLASSEX is a structure to describe the Window. */
	WNDCLASSEX windowclass;
	// We have to zero the memory
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	// cbSize configures the size of the window
	windowclass.cbSize = sizeof(WNDCLASSEX);
	// hbrBackground configures the color of the background
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	// lpszClassName is the name of the window - (not the window title)
	windowclass.lpszClassName = "MainWindow";
	// style = CS_HREDRAW | CS_VREDRAW allows for the redrawing of horizontal and vertical window
	// Allows for redrawing when vertially and horizontally
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowclass);

	// The rectangle specifys a width x height which will be  the size of the window
	// Default: 1024 by 768
	RECT rect = { 0, 0, kDefaultScreenWidth, kDefaultScreenHeight };
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);

	// We need to use rect because without using rect, the window will clip off a bit of dps to adjust for margins...
	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "SET Trek", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	return windowHandle;
}