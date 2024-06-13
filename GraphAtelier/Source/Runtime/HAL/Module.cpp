#include "Common/PCH.h"

#include "Module.h"

FModuleManager& FModuleManager::Get()
{
	static FModuleManager Inst;
	bool bFisrt = true;
	if (bFisrt)
	{
		Inst.LoadedModules.emplace(TSTR("None"), FModule());
	}
	return Inst;
}



const FModule& FModuleManager::LoadModule(const FPath& InPath, const FString& InName)
{
	FString FileName = InName;

	const FModule& None = LoadedModules[TSTR("None")];
	if (!FFileHelper::FileExist(InPath))
	{
		return None;
	}

	if (FileName.empty())
	{
		FileName = InPath.filename();
	}
	auto ExistingItem = LoadedModules.find(InName);
	if (ExistingItem != LoadedModules.end())
	{
		return ExistingItem->second;
	}

	void* PlatformHandle = PlatformLoadModule(InPath);
	if (!PlatformHandle)
	{
		return None;
	}
	FModule& NewModule = LoadedModules.emplace(FileName, FModule()).first->second;
	NewModule.Name = FileName;
	NewModule.PlatformHandle = PlatformHandle;
	NewModule.Path = InPath;

	return NewModule;
}

void FModuleManager::Shutdown()
{
	for (auto It = LoadedModules.begin(); It != LoadedModules.end(); ++It)
	{
		const FModule& Module = It->second;
		if (Module.IsVaild())
		{
			PlatformUnLoadModule(Module.PlatformHandle);
		}
		LoadedModules.erase(It);
	}
}

bool FModuleManager::UnloadModule(const FPath& InPath)
{
	for (auto It = LoadedModules.begin(); It != LoadedModules.end(); ++It)
	{
		if (It->second.Path == InPath)
		{
			LoadedModules.erase(It);
			return true;
		}
	}
	return false;
}

bool FModuleManager::UnloadModule(const FString& InName)
{
	auto FindModule = LoadedModules.find(InName);

	if (FindModule != LoadedModules.end())
	{
		const FModule& Module = FindModule->second;
		if (Module.IsVaild())
		{
			PlatformUnLoadModule(Module.PlatformHandle);
		}
		LoadedModules.erase(FindModule);
		return true;
	}
	return false;
}
