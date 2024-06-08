#pragma once

struct FBasicWindowInformation
{
	int32 Width;
	int32 Height;
	bool bConsole;
	void* PlatformHandle;
};

class FWindow
{
protected:
	FWindow(const FBasicWindowInformation& InBasicWindowInform)
		: BasicWindowInformation(InBasicWindowInform)
	{}

public:

	virtual void PumpMessage() = 0;

protected:
	FBasicWindowInformation BasicWindowInformation;
};