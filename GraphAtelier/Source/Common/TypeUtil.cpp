#include "Common/Type.h"

FString TrimLeft(const FString& TargetString)
{
    int32 TargetStringLen = TargetString.length();
    int32 Offset;
    for (Offset = 0; Offset < TargetStringLen; ++Offset)
    {
        if (TargetString[Offset] != TSTR(' '))
        {
            break;
        }
    }

    return TargetString.substr(Offset);
}

FString TrimRight(const FString& TargetString)
{
    int32 TargetStringLen = TargetString.length();
    int32 Offset;
    for (Offset = TargetStringLen - 1; Offset >= 0; --Offset)
    {
        if (TargetString[Offset] != TSTR(' '))
        {
            break;
        }
    }

    return TargetString.substr(0, Offset + 1);
}

FString Trim(const FString& TargetString)
{
    FString Ret;
    Ret = TrimLeft(TargetString);
    Ret = TrimRight(Ret);
    return Ret;
}

FArray<FString> Split(const FString& TargetString, const FString& Delim, const bool bTrim)
{
	FArray<FString> Ret;

    int32 DelimStartPosition = 0;
    FArray<int32> DelimStartPositions;
    while (true)
    {
        DelimStartPosition = TargetString.find(Delim, DelimStartPosition);

        if (DelimStartPosition == FString::npos)
        {
            break;
        }
        DelimStartPositions.push_back(DelimStartPosition);
        ++DelimStartPosition;
    }
    
    if (DelimStartPositions.size() == 0)
    {
        Ret.push_back(TargetString);
    }

    int32 DelimLen = Delim.length();
    for (int32 i = 0; i < DelimStartPositions.size(); ++i)
    {
        DelimStartPosition = DelimStartPositions[i];
        int32 NextDelimPosition = 0;
        int32 StartPosition = 0;
        int32 Count = 0;

        if (i + 1 < DelimStartPositions.size())
        {
            NextDelimPosition = DelimStartPositions[i + 1];
        }
        else // last delim position
        {
            NextDelimPosition = TargetString.length();
        }

        StartPosition += DelimStartPosition + DelimLen;
        Count = NextDelimPosition - StartPosition;

        FString Tokken = TargetString.substr(StartPosition, Count);
        if (!Tokken.empty())
        {
            if (bTrim)
            {
                Tokken = Trim(Tokken);
            }
            Ret.push_back(Tokken);
        }
    }

	return Ret;
}