#include "Common/PCH.h"

#include "Runtime/Engine/Engine.h"
#include "Runtime/Application/Application.h"

#include "imgui.h"

bool bProgrammExitRequested = false;

int32 MainEntry()
{
	int32 ExitCode = 0;
	try
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		GEngine.Initialize();
		while (!bProgrammExitRequested)
		{
			GEngine.Tick();
		}
		GEngine.ShutDown();
		ExitCode = GApplication->GetExitCode();
	}
	catch (const std::exception& e)
	{
		std::string Error = e.what();
		// TODO : Classify Why happens exception
		ExitCode = -1;
	}

	return ExitCode;
}