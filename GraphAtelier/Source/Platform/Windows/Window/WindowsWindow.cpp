#include "Common/PCH.h"

#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Window/Window.h"
#include "Platform/Windows/Window/WindowsWindow.h"

#include "Runtime/Application/Application.h"
#include "Platform/Windows/Window/WindowsWindowProc.h"

#include <iostream>

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
    static int32 WindowID = 0;

    if (!FWindow::Initialize())
    {
        return false;
    }

    if (BasicWindowInformation.bConsole)
    {
        if (!AllocConsole())
        {
            return false;
        }

        FILE* Dummy;
        freopen_s(&Dummy, "CONIN$", "r", stdin);
        freopen_s(&Dummy, "CONOUT$", "w", stderr);
        freopen_s(&Dummy, "CONOUT$", "w", stdout);

        HANDLE hStdout = CreateFile(TSTR("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        HANDLE hStdin = CreateFile(TSTR("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        SetStdHandle(STD_OUTPUT_HANDLE, hStdout);
        SetStdHandle(STD_ERROR_HANDLE, hStdout);
        SetStdHandle(STD_INPUT_HANDLE, hStdin);

        std::wclog.clear();
        std::clog.clear();
        std::wcout.clear();
        std::cout.clear();
        std::wcerr.clear();
        std::cerr.clear();
        std::wcin.clear();
        std::cin.clear();

        WindowClassName.resize(MAX_PATH);
        
        GetConsoleTitle(WindowClassName.data(), MAX_PATH);
        hWnd = FindWindow(NULL, WindowClassName.c_str());
        if (!hWnd)
        {
            return false;
        }

        WindowClassName = GApplication->GetTitle() + TSTR("_CONSOLE_WINDOW") + ToString(WindowID);
        SetConsoleTitle(WindowClassName.c_str());
    }
    else
    {
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

    if (BasicWindowInformation.bConsole)
    {
        FreeConsole();
    }

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
