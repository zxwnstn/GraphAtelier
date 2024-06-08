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

FString FCommandLine::Param(const FString& Param)
{
	auto Value = ValidCommands.find(Param);
	return Value != ValidCommands.end() ? Value->second : TSTR("");
}

bool FCommandLine::Has(const FString& Param)
{
	auto Value = ValidCommands.find(Param);
	return Value != ValidCommands.end();
}
