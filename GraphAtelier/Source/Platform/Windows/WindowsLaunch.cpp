#include "Common/PCH.h"
#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Engine/Command.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	FCommandLine::Get().Initialize(lpCmdLine);

	extern int32 MainEntry();
	int result = MainEntry();

	return result;
}