#pragma once
#include <filesystem>

using FPath = std::filesystem::path;

struct FPaths
{
	static FPath AbsoluteExecuatablePath;
	static FPath AbsoluteWorkingPath;
	static FPath RelativeRootPath;
	static FPath RelativeAssetPath;
	static FPath RelativeShaderPath;
	static FPath RelativeConfigPath;
	static FPath RelativeFirstPartyPath;
	static FPath RelativeThirdPartyPath;
};

struct FStringPaths
{
	static FString AbsoluteExecuatablePath;
	static FString AbsoluteWorkingPath;
	static FString RelativeRootPath;
	static FString RelativeAssetPath;
	static FString RelativeShaderPath;
	static FString RelativeConfigPath;
	static FString RelativeFirstPartyPath;
	static FString RelativeThirdPartyPath;
};

class FFile
{
public:
	bool IsValid();
	bool IsBinary();
	
	int32 GetSize();
	const FPath& GetPath();
	const FString& GetContent();
	const void ClearContentMemory();

private:
	FPath Path;
	FPath Name;
	FString Content;
	int32 Size = 0;
	bool bIsBinary;

	friend class FFileHelper;
};

class FFileHelper
{
public:
	static FPath GetWorkingDirectory();
	static void SetWorkingDirectory(const FString& InPath);
	static void SetWorkingDirectory(const FPath& InPath);

	static bool FileExist(const FString& InPath);
	static bool FileExist(const FPath& InPath);
	static bool DirectoryExist(const FString& InPath);
	static bool DirectoryExist(const FPath& InPath);

	static bool IsRelative(const FString& InPath);
	static bool IsRelative(const FPath& InPath);
	static bool IsAbsolute(const FString& InPath);
	static bool IsAbsolute(const FPath& InPath);

	static FString GetAbsolutePath(const FString& InRelativePath);
	static FPath GetAbsolutePath(const FPath& InRelativePath);
	static FString GetAbsoluteIncludeDirectory(const FString& InFilePath);
	static FPath GetAbsoluteIncludeDirectory(const FPath& InFilePath);

	static FFile ReadFile(const FString& InPath, bool InIsBinary = false);
	static FFile ReadFile(const FPath& InPath, bool InIsBinary = false);
	static FFile WriteFile(const FString& InPath, FString& InContent, bool InIsBinary);
	static FFile WriteFile(const FPath& FilePath, FString& InContent, bool InIsBinary);

	static bool InitializePaths();
};

