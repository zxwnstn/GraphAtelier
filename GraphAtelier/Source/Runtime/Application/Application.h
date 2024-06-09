#pragma once

#include "Runtime/Window/Window.h"

class FApplication
{
public:
	virtual bool Initialize();
	virtual void ShutDown();

	const FBasicWindowInformation& GetMainWindowInformation();
	int32 GetExitCode() { return ExitCode; }
	virtual void* GetHandle() = 0;
	FString GetTitle() { return Title; }

private:
	FString Title;
	int32 ExitCode;

	FBasicWindowInformation BasicWindowInformation;
};

extern FApplication* GApplication;