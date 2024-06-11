#include "Common/PCH.h"

#include "Application.h"
#include "Runtime/Util/Ini.h"
#include "Runtime/Util/File.h"
FApplication* GApplication = nullptr;

bool FApplication::Initialize()
{
	// TODO : Log Initialize
	
	// Path Setting
	if (!FFileHelper::InitializePaths())
	{
		return false;
	}

	// Read Ini
	const FIni& DefaultSettingIni = FIniManager::Get().ReadIni(FPaths::RelativeConfigPath, TSTR("DefaultSetting"));
	if (DefaultSettingIni.IsValid())
	{
		Title = DefaultSettingIni.GetValue(TSTR("Title"));
		// TODO : Log Title and BasicWindowInformation

		BasicWindowInformation.Height = DefaultSettingIni.GetValueAsInt32(TSTR("Height"));
		BasicWindowInformation.Width = DefaultSettingIni.GetValueAsInt32(TSTR("Width"));
		BasicWindowInformation.WindowScreenPosX = DefaultSettingIni.GetValueAsInt32(TSTR("WindowScreenPosX"));
		BasicWindowInformation.WindowScreenPosY = DefaultSettingIni.GetValueAsInt32(TSTR("WindowScreenPosY"));
		BasicWindowInformation.bConsole = false;
		BasicWindowInformation.PlatformHandle = nullptr;
	}
	return true;
}

void FApplication::ShutDown()
{
}

const FBasicWindowInformation& FApplication::GetMainWindowInformation()
{
	return BasicWindowInformation;
}
