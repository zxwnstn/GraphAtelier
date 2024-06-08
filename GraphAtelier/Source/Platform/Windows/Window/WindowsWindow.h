#pragma once

class FWindowsWindow 
	: public FWindow
{
private:
	FWindowsWindow(const FBasicWindowInformation& InBasicWindowInform);

public:

	void PumpMessage();
	void Tick();

	friend FWindow* CreatePlatformWindow(const FBasicWindowInformation& InBasicWindowInform);
};