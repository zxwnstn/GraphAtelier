#include "Common/PCH.h"

#include "Platform/Windows/WindowsCommon.h"

#include "Runtime/Application/Application.h"
#include "Platform/Windows/WindowsAppliacation.h"
#include "Runtime/Util/File.h"

FWindowsApplication::FWindowsApplication(HINSTANCE InInstance)
	: Instance(InInstance)
{
}

bool FWindowsApplication::Initialize()
{
	FStringPaths::AbsoluteExecuatablePath.resize(MAX_PATH);
	GetModuleFileName(NULL, FStringPaths::AbsoluteExecuatablePath.data(), MAX_PATH);

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
