#include "Common/Type.h"

#if UNICODE
    #define _ToString std::to_wstring
#else
    #define _ToString std::to_string
#endif

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
	if (TargetString.empty())
	{
		return Ret;
	}

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
        return Ret;
    }
    
    {
        FString FirstTokken = TargetString.substr(0, DelimStartPositions[0]);
        if (!FirstTokken.empty())
        {
            Ret.push_back(FirstTokken);
        }
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

int32 ToInt32(const FString& TargetString)
{
    return std::stoi(TargetString);
}

float ToFloat(const FString& TargetString)
{
    return std::stof(TargetString);
}

FString ToString(const int32 TargetInt)
{
    return _ToString(TargetInt);
}

FAnsiString ConvertAnsiString(const FString& TargetString)
{
#if UNICODE
    return FAnsiString(TargetString.begin() , TargetString.end());
#else
    return TargetString;
#endif
}

FWideString ConvertWideString(const FString& TargetString)
{
#if UNICODE
	return TargetString;
#else
	return FWideString(TargetString.begin(), TargetString.end());
#endif
}

#if UNICODE
FWideString ConvertWideString(const FAnsiString& TargetString)
{
    return FWideString(TargetString.begin(), TargetString.end());
}
#else
FAnsiString ConvertAnsiString(const FWideString& TargetString)
{
    return FAnsiString(TargetString.begin(), TargetString.end());
}
#endif
