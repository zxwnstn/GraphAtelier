#include <string>
#include <sstream>

using FWideString = std::wstring;
using FWideStream = std::wstringstream;
using FAnsiString = std::string;
using FAnsiStream = std::stringstream;

#if _UNICODE
	using FString = FWideString;
	using FStringStream = FWideStream;
#else
	using FString = FAnsiString;
	using FStringStream = FAnsiStream;
#endif

#define COMMON_INVALID_INT -1
#define COMMON_INVALID_FLOAT 1E+37

#include <unordered_map>

template<typename Key, typename Value>
using FMap = std::unordered_map<Key, Value>;

#include <vector>

template<typename Elem>
using FArray = std::vector<Elem>;

#if _UNICODE
	#define TSTR(str) L##str
#else
	#define TSTR(str) = str
#endif

#if _WIN32
using int32 = int;
using int64 = long long;
#endif

// TypeUtil
extern FArray<FString> Split(const FString& TargetString, const FString& Delim, const bool bTrim);
extern FString TrimLeft(const FString& TargetString);
extern FString TrimRight(const FString& TargetString);
extern int32 ToInt32(const FString& TargetString);
extern float ToFloat(const FString& TargetString);
extern FString ToString(const int32 TargetInt);

extern FAnsiString ConvertAnsiString(const FString& TargetString);
extern FWideString ConvertWideString(const FString& TargetString);

#if UNICODE
	extern FWideString ConvertWideString(const FAnsiString& TargetString);
#else
	extern FAnsiString ConvertAnsiString(const FWideString& TargetString);
#endif
