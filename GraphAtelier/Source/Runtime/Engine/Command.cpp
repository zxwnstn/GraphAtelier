#include "Common/PCH.h"
#include "Command.h"

FCommandLine& FCommandLine::Get()
{
	static FCommandLine CommandLine;
	return CommandLine;
}

void FCommandLine::Initialize(const FString& InOriginalCommandLine)
{
	static bool Initialized = false;
	if (Initialized)
	{
		return;
	}
	Initialized = true;
	OriginalCommandLine = InOriginalCommandLine;
	FArray<FString> CommandList = Split(OriginalCommandLine, TSTR("-"), true);

	for (const FString& Command : CommandList)
	{
		FArray<FString> CommandParam = Split(Command, TSTR("="), true);
		ValidCommands.emplace(CommandParam[0], CommandParam.size() == 1 ? FString(TSTR("")) : CommandParam[1]);
	}
}

bool FCommandLine::Param(const FString& InParam, FString& OutValue)
{
	auto Value = ValidCommands.find(InParam);
	OutValue = Value != ValidCommands.end() ? Value->second : TSTR("");
	return Value != ValidCommands.end();
}

bool FCommandLine::Has(const FString& Param)
{
	auto Value = ValidCommands.find(Param);
	return Value != ValidCommands.end();
}
