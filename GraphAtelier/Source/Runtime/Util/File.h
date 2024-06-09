#pragma once

class FFile
{
public:
	FString Path;
	FString Content;
	int32 Size;
	bool bIsBinary;
};


class FFileHelper
{
public:
	static FString GetCurrentDirectory();
	static void SetCurrentDirectory(const FString& Path);

	static bool FileExist(const FString& Path);
	static bool DirectoryExist(const FString& Path);

	static FString GetAbsolutePath(const FString& RelativePath);

	static FFile ReadFile(const FString& FilePath, bool InIsBinary = false);
	static FFile WriteFile(const FString& FilePath, FString& In, bool InIsBinary);
};