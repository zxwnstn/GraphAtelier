#include "Common/PCH.h"

#include "Runtime/Util/Ini.h"

static const FString IniFileExtension = FString(TSTR("ini"));
static const FString IniFileDotExtension = FString(TSTR(".ini"));

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

int32 FIni::GetValueAsInt32(const FString& ConfigName, const FString& SectionName) const
{
	FString Value = GetValue(ConfigName, SectionName);
	return Value.empty() ? COMMON_INVALID_INT : ToInt32(Value);
}

float FIni::GetValueAsFloat(const FString& ConfigName, const FString& SectionName) const
{
	FString Value = GetValue(ConfigName, SectionName);
	return Value.empty() ? COMMON_INVALID_FLOAT : ToFloat(Value);
}

bool FIni::IsValid() const
{
	return !FullPath.empty() && !Name.empty();
}

const FIni& FIniManager::ReadIni(const FString& InPath, const FString& InIniName)
{
	return ReadIni(FPath(InPath), InIniName);
}

const FIni& FIniManager::ReadIni(const FPath& InPath, const FString& InIniName)
{
	bool bIsDirectory = FFileHelper::DirectoryExist(InPath);
	bool bIsFile = FFileHelper::FileExist(InPath);

	if (!bIsDirectory && !bIsFile)
	{
		return IniMap.find(TSTR("None"))->second;
	}

	FIni& Ini = IniMap.emplace(InIniName, FIni()).first->second;

	Ini.Name = InIniName;
	if (bIsDirectory)
	{
		FString FullPath = FString(InPath) + FString(TSTR("/")) + InIniName + IniFileDotExtension;
		Ini.FullPath = FFileHelper::GetAbsolutePath(FullPath);
	}
	else if (Ini.FullPath.extension().compare(IniFileExtension))
	{
		Ini.FullPath = FFileHelper::GetAbsolutePath(InPath);
	}
	else
	{
		// TODO : Add Log
	}
	
	FFile File = FFileHelper::ReadFile(Ini.FullPath);
	if (!File.IsValid())
	{
		return Ini;
	}

	FIniSection* DefaultSection = &Ini.SectionMap.emplace(TSTR("Default"), FIniSection()).first->second;
	FIniSection* CurrentSection = DefaultSection;

	FStringStream StringStream(File.GetContent());
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
	File.ClearContentMemory();

	return Ini;
}

FIni FIniManager::WriteIni(const FString& InPath, const FString& IniName)
{
	return FIni();
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

const FIni& FIniManager::GetIni(const FString& IniName)
{
	auto It = IniMap.find(IniName);
	bool bHasIni = It != IniMap.end();
	if (bHasIni)
	{
		return It->second;
	}

	return IniMap[TSTR("None")];
}
