#include "Common/PCH.h"

#include <fstream>
#include "Runtime/Engine/Command.h"
#include "File.h"

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


FPath FPaths::AbsoluteExecuatablePath;
FPath FPaths::AbsoluteWorkingPath;
FPath FPaths::RelativeAssetPath;
FPath FPaths::RelativeConfigPath;
FPath FPaths::RelativeRootPath;
FPath FPaths::RelativeShaderPath;

FString FStringPaths::AbsoluteExecuatablePath;
FString FStringPaths::AbsoluteWorkingPath;
FString FStringPaths::RelativeAssetPath;
FString FStringPaths::RelativeConfigPath;
FString FStringPaths::RelativeRootPath;
FString FStringPaths::RelativeShaderPath;

FPath FFileHelper::GetWorkingDirectory()
{
	return filesystem::current_path().generic_tstring();
}

void FFileHelper::SetWorkingDirectory(const FString& InPath)
{
	SetWorkingDirectory(FPath(InPath));
}

void FFileHelper::SetWorkingDirectory(const FPath& InPath)
{
	if (DirectoryExist(InPath))
	{
		filesystem::current_path(InPath);
	}
}

bool FFileHelper::FileExist(const FString& InPath)
{
	return FileExist(FPath(InPath));
}

bool FFileHelper::FileExist(const FPath& InPath)
{
	return filesystem::exists(InPath) && filesystem::is_regular_file(InPath);
}

bool FFileHelper::DirectoryExist(const FString& InPath)
{
	return DirectoryExist(FPath(InPath));
}

bool FFileHelper::DirectoryExist(const FPath& InPath)
{
	return filesystem::exists(InPath) && filesystem::is_directory(InPath);
}

bool FFileHelper::IsRelative(const FString& InPath)
{
	return IsRelative(FPath(InPath));
}

bool FFileHelper::IsRelative(const FPath& InPath)
{
	return InPath.is_relative();
}

bool FFileHelper::IsAbsolute(const FString& InPath)
{
	return IsAbsolute(FPath(InPath));
}

bool FFileHelper::IsAbsolute(const FPath& InPath)
{
	return InPath.is_absolute();
}

FString FFileHelper::GetAbsolutePath(const FString& InPath)
{
	FPath Path(InPath);
	return filesystem::absolute(Path).generic_tstring();
}

FPath FFileHelper::GetAbsolutePath(const FPath& InPath)
{
	return filesystem::absolute(InPath);
}

FString FFileHelper::GetAbsoluteIncludeDirectory(const FString& InPath)
{
	return GetAbsoluteIncludeDirectory(FPath(InPath));
}

FPath FFileHelper::GetAbsoluteIncludeDirectory(const FPath& InPath)
{
	if (filesystem::exists(InPath))
	{
		FPath Path;

		if (filesystem::is_regular_file(InPath))
		{
			Path = InPath.parent_path();
		}
		else if (filesystem::is_directory(Path))
		{
		}
		else
		{
			Assert(false);
		}

		return Path;
	}

	return FPath();
}

FFile FFileHelper::ReadFile(const FString& InFilePath, bool InIsBinary)
{
	return ReadFile(FPath(InFilePath), InIsBinary);
}

FFile FFileHelper::ReadFile(const FPath& InFilePath, bool InIsBinary)
{
	FFile File;
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

	File.Path = InFilePath;
	File.Name = File.Path.filename();
	File.bIsBinary = InIsBinary;

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

FFile FFileHelper::WriteFile(const FPath& FilePath, FString& InContent, bool InIsBinary)
{
	return FFile();
}

bool FFileHelper::InitializePaths()
{
	static bool bInitialized = false;
	if (bInitialized)
	{
		return false;
	}
	bInitialized = true;

	FStringPaths::AbsoluteWorkingPath = GetWorkingDirectory();

	FString TargetWorkingPath;
	if (FCommandLine::Get().Param(TSTR("SetWorkingDirectory"), TargetWorkingPath))
	{
		if (TargetWorkingPath.empty())
		{
			TargetWorkingPath = FStringPaths::AbsoluteExecuatablePath;
			FStringPaths::AbsoluteWorkingPath = FPath(TargetWorkingPath).parent_path();
		}
		else
		{
			FStringPaths::AbsoluteWorkingPath = TargetWorkingPath;
		}
		SetWorkingDirectory(FStringPaths::AbsoluteWorkingPath);
	}

	// Assume workspace sets in default build directory
	FStringPaths::RelativeRootPath = TSTR("../");
	FStringPaths::RelativeAssetPath = FStringPaths::RelativeRootPath + TSTR("/Asset");
	FStringPaths::RelativeConfigPath = FStringPaths::RelativeRootPath + TSTR("/Config");
	FStringPaths::RelativeShaderPath = FStringPaths::RelativeRootPath + TSTR("/Source/Shader");

	// Sanity check
	bool bPathIsCorredtlySet = DirectoryExist(FStringPaths::RelativeAssetPath) 
		&& DirectoryExist(FStringPaths::RelativeConfigPath)
		&& DirectoryExist(FStringPaths::RelativeShaderPath);
	Assert(bPathIsCorredtlySet);
	if (!bPathIsCorredtlySet)
	{
		return false;
	}

	FPaths::AbsoluteExecuatablePath = FStringPaths::AbsoluteExecuatablePath;
	FPaths::AbsoluteWorkingPath = FStringPaths::AbsoluteWorkingPath;
	FPaths::RelativeRootPath = FStringPaths::RelativeRootPath;
	FPaths::RelativeConfigPath = FStringPaths::RelativeConfigPath;
	FPaths::RelativeShaderPath = FStringPaths::RelativeShaderPath;

	return true;
}

bool FFile::IsValid()
{
	return Size != 0 && !Name.empty();
}

bool FFile::IsBinary()
{
	return bIsBinary;
}

int32 FFile::GetSize()
{
	return Size;
}

const FPath& FFile::GetPath()
{
	return Path;
}

const FString& FFile::GetContent()
{
	return Content;
}

const void FFile::ClearContentMemory()
{
	Content.clear();
}
