#pragma once

#include "Runtime/Window/Window.h"

class FApplication
{
public:
	bool Initialize();
	void ShutDown();

	FBasicWindowInformation GetMainWindowInformation();
	int32 GetExitCode() { return ExitCode; }

private:
	int32 ExitCode;
};

extern FApplication GApplication;