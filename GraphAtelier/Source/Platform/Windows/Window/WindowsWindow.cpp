#include "Common/PCH.h"

#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Window/Window.h"
#include "Platform/Windows/Window/WindowsWindow.h"

#include "Runtime/Application/Application.h"
#include "Platform/Windows/Window/WindowsWindowProc.h"

FWindow* CreatePlatformWindow(const FBasicWindowInformation& InWindowInform)
{
	return new FWindowsWindow(InWindowInform);
}

FWindowsWindow::FWindowsWindow(const FBasicWindowInformation& InBasicWindowInform)
	: FWindow(InBasicWindowInform)
{
}

bool FWindowsWindow::Initialize()
{
    if (!FWindow::Initialize())
    {
        return false;
    }

    if (BasicWindowInformation.bConsole)
    {
        AllocConsole();
    }
    else
    {
        static int32 WindowID = 0;

        WindowClassName = GApplication->GetTitle() + TSTR("_WINDOW") + ToString(WindowID);

        ZeroMemory(&WindowClass, sizeof(WNDCLASSEX));
        WindowClass.cbSize = sizeof(WNDCLASSEX);
        WindowClass.style = CS_HREDRAW | CS_VREDRAW;
        WindowClass.lpfnWndProc = DefaultWndProc;
        WindowClass.cbClsExtra = 0;
        WindowClass.cbWndExtra = 0;
        WindowClass.hInstance = (HINSTANCE)GApplication->GetHandle();
        WindowClass.hIcon = LoadIcon(WindowClass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
        WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        WindowClass.lpszMenuName = nullptr;
        WindowClass.lpszClassName = WindowClassName.c_str();
        WindowClass.hIconSm = LoadIcon(WindowClass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
        RegisterClassExW(&WindowClass);

        hWnd = CreateWindow(
            WindowClass.lpszClassName,
            GApplication->GetTitle().c_str(),
            WS_OVERLAPPEDWINDOW,
            BasicWindowInformation.WindowScreenPosX, BasicWindowInformation.WindowScreenPosY, 
            BasicWindowInformation.Width, BasicWindowInformation.Height,
            nullptr, nullptr, WindowClass.hInstance, nullptr);

        if (!hWnd)
        {
            return false;
        }
        ++WindowID;
    }

	return true;
}

void FWindowsWindow::Shutdown()
{
    FWindow::Shutdown();

    CloseHandle(hWnd);
    UnregisterClass(WindowClassName.c_str(), WindowClass.hInstance);
}

void FWindowsWindow::Tick()
{
	FWindow::Tick();

    UpdateWindow(hWnd);
}

void FWindowsWindow::PumpMessage()
{
    MSG Msg;
    if (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (Msg.message != WM_QUIT)
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
    }
    
}

void FWindowsWindow::Show()
{
    ShowWindow(hWnd, SW_NORMAL);
}

void FWindowsWindow::Hide()
{
    CloseWindow(hWnd);
}
