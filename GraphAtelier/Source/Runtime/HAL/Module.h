#pragma once

#include "File.h"

void* PlatformLoadModule(const FPath& InPath);
void PlatformUnLoadModule(const void* PlatformModuleHandle);

struct FModule
{
	bool IsVaild() const { return PlatformHandle != nullptr; }

	FString Name;
	FPath Path;
	void* PlatformHandle;
};

class FModuleManager
{
public:
	static FModuleManager& Get();

	const FModule& LoadModule(const FPath& InPath, const FString& InName = FString());
	bool UnloadModule(const FString& InName);
	bool UnloadModule(const FPath& InPath);
	void Shutdown();

private:
	FMap<FString, FModule> LoadedModules;
};