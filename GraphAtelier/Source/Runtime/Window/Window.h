#pragma once

struct FBasicWindowInformation
{
	int32 Width;
	int32 Height;
	int32 WindowScreenPosX;
	int32 WindowScreenPosY;
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

	virtual bool Initialize();
	virtual void Shutdown();

	virtual void Tick();
	virtual void PumpMessage() = 0;
	virtual void Show() {}
	virtual void Hide() {}

protected:
	FBasicWindowInformation BasicWindowInformation;
};