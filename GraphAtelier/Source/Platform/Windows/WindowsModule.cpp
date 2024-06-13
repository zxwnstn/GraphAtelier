#include "Common/PCH.h"

#include "WindowsCommon.h"
#include "Runtime/HAL/Module.h"

void* PlatformLoadModule(const FPath& InPath)
{
	HMODULE Module = LoadLibrary(InPath.c_str());

	return static_cast<void*>(Module);
}

void PlatformUnLoadModule(const void* PlatformModuleHandle)
{
	FreeLibrary(HMODULE(PlatformModuleHandle));
}
