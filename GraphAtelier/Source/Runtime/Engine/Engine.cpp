#include "Common/PCH.h"

#include "Engine.h"
#include "Runtime/Application/Application.h"
#include "Command.h"

#include "Pointage/Include/Pointage.h"

#include <Windows.h>
FEngine GEngine;

void FEngine::Initialize()
{
	// Crate Main Window
	extern FWindow* CreatePlatformWindow(const FBasicWindowInformation&);
	if (!MainWindow)
	{
		const FBasicWindowInformation& BasicWindowInformation = GApplication->GetMainWindowInformation();
		MainWindow = CreatePlatformWindow(BasicWindowInformation);
		MainWindow->Initialize();
		Windows.push_back(MainWindow);
	}

#if BUILD_DEBUG
	if (FCommandLine::Get().Has(TSTR("CreateConsole")))
	{
		FBasicWindowInformation ConsoleWindowInformation;
		ConsoleWindowInformation.bConsole = true;
		Windows.push_back(CreatePlatformWindow(ConsoleWindowInformation));
	}
#endif

	MainWindow->Show();

	// Initialize Pointage
	auto v = LoadLibrary(L"Pointage.dll");
	Pointage::ATest::Init();
	Pointage::Initialize();
}

void FEngine::ShutDown()
{
	for (FWindow* Window : Windows)
	{
		Window->Shutdown();
		delete Window;
	}
	Windows.clear();
}

int FEngine::Tick()
{
	PumpMessages();

	return 0;
}

void FEngine::PumpMessages()
{
	for (FWindow* Window : Windows)
	{
		Window->PumpMessage();
	}
}
