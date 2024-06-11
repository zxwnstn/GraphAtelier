#pragma once
#include "File.h"

using FIniSection = FMap<FString, FString>;

struct FIni
{
	FString GetValue(const FString& ConfigName, const FString& SectionName = FString()) const;
	int32 GetValueAsInt32(const FString& ConfigName, const FString& SectionName = FString()) const;
	float GetValueAsFloat(const FString& ConfigName, const FString& SectionName = FString()) const;
	bool IsValid() const;

	FMap<FString, FIniSection> SectionMap;
	FPath FullPath;
	FString Name;
};

class FIniManager;


class FIniManager
{
public:
	static FIniManager& Get();

	const FIni& GetIni(const FString& IniName);

	const FIni& ReadIni(const FString& InPath, const FString& IniName);
	const FIni& ReadIni(const FPath& InPath, const FString& IniName);
	FIni WriteIni(const FString& InPath, const FString& IniName);

	FMap<FString, FIni> IniMap;
};


