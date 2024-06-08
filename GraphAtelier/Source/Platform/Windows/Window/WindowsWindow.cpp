#include "Common/PCH.h"

#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Window/Window.h"
#include "Platform/Windows/Window/WindowsWindow.h"

FWindow* CreatePlatformWindow(const FBasicWindowInformation& InWindowInform)
{
	return new FWindowsWindow(InWindowInform);
}

FWindowsWindow::FWindowsWindow(const FBasicWindowInformation& InBasicWindowInform)
	: FWindow(InBasicWindowInform)
{
	if (BasicWindowInformation.bConsole)
	{
		AllocConsole();
	}
}

void FWindowsWindow::PumpMessage()
{

}

void FWindowsWindow::Tick()
{
}
