#include "Common/PCH.h"

#include "Engine.h"
#include "Runtime/Application/Application.h"
#include "Command.h"

FEngine GEngine;

void FEngine::Initialize()
{
	extern FWindow* CreatePlatformWindow(const FBasicWindowInformation&);
	if (!MainWindow)
	{
		FBasicWindowInformation BasicWindowInformation = GApplication.GetMainWindowInformation();
		MainWindow = CreatePlatformWindow(BasicWindowInformation);
		Windows.push_back(MainWindow);
	}

	if (FCommandLine::Get().Has(TSTR("CreateConsole")))
	{
		FBasicWindowInformation ConsoleWindowInformation;
		ConsoleWindowInformation.bConsole = true;
		Windows.push_back(CreatePlatformWindow(ConsoleWindowInformation));
	}
}

void FEngine::ShutDown()
{
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
