#pragma once

class FCommandLine
{
private:
	FCommandLine() = default;

public:
	static FCommandLine& Get();
	
public:
	void Initialize(const FString& InOriginalCommandLine);

	bool Param(const FString& InParam, FString& OutValue);
	bool Has(const FString& InParam);

	const FString& GetOriginalCommandLine() const
	{
		return OriginalCommandLine;
	}

private:
	FString OriginalCommandLine;
	FMap<FString, FString> ValidCommands;
};