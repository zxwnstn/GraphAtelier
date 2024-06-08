#include "Common/PCH.h"

#include "Runtime/Engine/Engine.h"
#include "Runtime/Application/Application.h"

bool bProgrammExitRequested = false;

int32 MainEntry()
{
	int32 ExitCode = 0;
	try
	{
		if (!GApplication.Initialize())
		{
			bProgrammExitRequested = true;
		}

		GEngine.Initialize();
		while (!bProgrammExitRequested)
		{
			GEngine.Tick();
		}
		GEngine.ShutDown();

		ExitCode = GApplication.GetExitCode();
		GApplication.ShutDown();
	}
	catch (const std::exception& e)
	{
		std::string Error = e.what();
		// TODO : Classify Why happens exception
		ExitCode = -1;
	}

	return ExitCode;
}