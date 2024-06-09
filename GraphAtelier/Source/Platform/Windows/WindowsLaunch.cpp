#include "Common/PCH.h"
#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Engine/Command.h"
#include "Runtime/Application/Application.h"
#include "Platform/Windows/WindowsAppliacation.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	FCommandLine::Get().Initialize(lpCmdLine);
	GApplication = new FWindowsApplication(hInstance);
	GApplication->Initialize();

	extern int32 MainEntry();
	int result = MainEntry();

	GApplication->ShutDown();
	delete GApplication;

	return result;
}