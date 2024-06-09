#include "Common/PCH.h"

#include "Runtime/Util/Ini.h"
#include "Runtime/Util/File.h"

FString FIni::GetValue(const FString& ConfigName, const FString& SectionName) const
{
	if (!SectionName.empty())
	{
		const auto& Section = SectionMap.find(SectionName);
		if (Section != SectionMap.end())
		{
			auto It = Section->second.find(ConfigName);
			if (It != Section->second.end())
			{
				return It->second;
			}
		}
	}
	else
	{
		for (const auto& Section : SectionMap)
		{
			auto It = Section.second.find(ConfigName);
			if (It != Section.second.end())
			{
				return It->second;
			}
		}
	}

	return FString();
}

const FIni& FIniManager::ReadIni(const FString& InPath, const FString& InIniName)
{
	if (!FFileHelper::FileExist(InPath))
	{
		return IniMap.find(TSTR("None"))->second;
	}

	 FIni& Ini = IniMap.emplace(InIniName, FIni()).first->second;
	
	 Ini.Name = InIniName;
	 Ini.FullPath = FFileHelper::GetAbsolutePath(InPath);


	FIniSection* DefaultSection = &Ini.SectionMap.emplace(TSTR("Default"), FIniSection()).first->second;
	FIniSection* CurrentSection = DefaultSection;
	
	FFile File = FFileHelper::ReadFile(InPath);
	FStringStream StringStream(File.Content);
	while (!StringStream.eof())
	{
		FString Line;
		StringStream >> Line;

		if (Line._Starts_with(TSTR("[")))
		{
			FString SectionName = Line.substr(1, Line.size() - 2);
			CurrentSection = &Ini.SectionMap.emplace(SectionName, FIniSection()).first->second;
		}
		else if (Line.empty())
		{
			CurrentSection = DefaultSection;
		}
		else
		{
			FArray<FString> KeyValue = Split(Line, TSTR("="), true);
			CurrentSection->emplace(KeyValue[0], KeyValue.size() > 1 ? KeyValue[1] : TSTR(""));
		}
	}

	return Ini;
}

FIniManager& FIniManager::Get()
{
	static FIniManager Manager;
	static bool bFirst = true;
	if (bFirst)
	{
		Manager.IniMap.emplace(TSTR("None"), FIni());
		bFirst = false;
	}
	return Manager;
}

const bool FIniManager::GetIni(const FString& IniName, FIni& OutIni)
{


	return true;
}
