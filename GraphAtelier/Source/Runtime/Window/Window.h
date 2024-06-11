#pragma once

struct FBasicWindowInformation
{
	int32 Width = 0; 
	int32 Height = 0;
	int32 WindowScreenPosX = 0;
	int32 WindowScreenPosY = 0;
	bool bConsole = false;
	void* PlatformHandle = nullptr;
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