#include "Common/PCH.h"

#include "Application.h"
#include "Runtime/Util/Ini.h"

FApplication* GApplication = nullptr;

bool FApplication::Initialize()
{
	// Path Setting
	
	// BasicWindowInformation Setting
	const FIni& Ini = FIniManager::Get().ReadIni(TSTR("E:\\dev\\GraphAtelier\\GraphAtelier\\Config\\DefaultSetting.ini"), TSTR("DefaultSetting"));
	BasicWindowInformation.Height = ToInt32(Ini.GetValue(TSTR("Height")));
	BasicWindowInformation.Width = ToInt32(Ini.GetValue(TSTR("Width")));
	BasicWindowInformation.WindowScreenPosX = ToInt32(Ini.GetValue(TSTR("WindowScreenPosX")));
	BasicWindowInformation.WindowScreenPosY = ToInt32(Ini.GetValue(TSTR("WindowScreenPosY")));
	BasicWindowInformation.bConsole = false;
	BasicWindowInformation.PlatformHandle = nullptr;

	Title = Ini.GetValue(TSTR("Title"));

	return true;
}

void FApplication::ShutDown()
{
}

const FBasicWindowInformation& FApplication::GetMainWindowInformation()
{
	return BasicWindowInformation;
}
