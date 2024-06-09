#pragma once


using FIniSection = FMap<FString, FString>;

struct FIni
{
	FString GetValue(const FString& ConfigName, const FString& SectionName = FString()) const;
	
	FMap<FString, FIniSection> SectionMap;
	FString FullPath;
	FString Name;
};

class FIniManager;


class FIniManager
{
public:
	static FIniManager& Get();

	const bool GetIni(const FString& IniName, FIni& OutIni);

	const FIni& ReadIni(const FString& InPath, const FString& IniName);
	FIni WriteIni(const FString& InPath, const FString& IniName);

	FMap<FString, FIni> IniMap;
};


