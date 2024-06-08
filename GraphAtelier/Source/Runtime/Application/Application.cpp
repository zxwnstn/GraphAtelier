#include "Common/PCH.h"

#include "Application.h"

FApplication GApplication;

bool FApplication::Initialize()
{
	return true;
}

void FApplication::ShutDown()
{
}

FBasicWindowInformation FApplication::GetMainWindowInformation()
{
	FBasicWindowInformation Ret;
	Ret.PlatformHandle = nullptr;

	return Ret;
}
