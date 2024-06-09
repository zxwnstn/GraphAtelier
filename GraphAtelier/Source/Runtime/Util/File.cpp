#include "Common/PCH.h"

#include "File.h"
#include <fstream>
#include <filesystem>

using namespace std;

#if UNICODE 
	using InputFileStream = std::wifstream;
	using OutputFileStream = std::wofstream;
	#define generic_tstring generic_wstring
#else
	using InputFileStream = std::ifstream;
	using OutputFileStream = std::ofstream;
#define generic_tstring generic_string
#endif


FString FFileHelper::GetCurrentDirectory()
{
	return filesystem::current_path().generic_tstring();
}

void FFileHelper::SetCurrentDirectory(const FString& Path)
{
	if (DirectoryExist(Path))
	{
		filesystem::current_path(Path);
	}
}

bool FFileHelper::FileExist(const FString& InPath)
{
	filesystem::path Path(InPath);
	return filesystem::exists(Path) && filesystem::is_regular_file(Path);
}

bool FFileHelper::DirectoryExist(const FString& InPath)
{
	filesystem::path Path(InPath);
	return filesystem::exists(Path) && filesystem::is_directory(Path);
}

FString FFileHelper::GetAbsolutePath(const FString& RelativePath)
{
	if (filesystem::exists(RelativePath))
	{
		filesystem::path Path(RelativePath);
		return filesystem::absolute(Path).generic_tstring();
	}

	return FString();
}

FFile FFileHelper::ReadFile(const FString& InFilePath, bool InIsBinary)
{
	FFile File;
	File.Size = 0;

	if (!FileExist(InFilePath))
	{
		return File;
	}
	InputFileStream FileStream;

	if (InIsBinary)
	{
		FileStream.open(InFilePath, std::ios_base::binary);
	}
	else
	{
		FileStream.open(InFilePath, std::ios_base::in);
	}

	if (!FileStream.is_open())
	{
		return File;
	}
	FileStream.seekg(0, std::ios::end);
	File.Size = FileStream.tellg();

	File.Content.resize(File.Size);
	FileStream.seekg(0, std::ios::beg);

	FileStream.read(&File.Content[0], File.Size);
	FileStream.close();

	return File;
}

FFile FFileHelper::WriteFile(const FString& FilePath, FString& In, bool InIsBinary)
{

	return FFile();
}
