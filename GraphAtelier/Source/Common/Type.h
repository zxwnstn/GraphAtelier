#include <string>
#include <sstream>

#if _UNICODE
	using FString = std::wstring;
	using FStringStream = std::wstringstream;
#else
	using FString = std::string;
	using FStringStream = std::stringstream;
#endif


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
