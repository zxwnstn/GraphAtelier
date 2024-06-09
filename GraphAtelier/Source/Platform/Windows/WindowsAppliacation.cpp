#include "Common/PCH.h"

#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Application/Application.h"
#include "Platform/Windows/WindowsAppliacation.h"


FWindowsApplication::FWindowsApplication(HINSTANCE InInstance)
	: Instance(InInstance)
{
}

bool FWindowsApplication::Initialize()
{
	FApplication::Initialize();
	return true;
}

void FWindowsApplication::ShutDown()
{
}

void* FWindowsApplication::GetHandle()
{
	return Instance;
}
