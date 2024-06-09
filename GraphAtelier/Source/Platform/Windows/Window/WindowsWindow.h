#pragma once

class FWindowsWindow 
	: public FWindow
{
private:
	FWindowsWindow(const FBasicWindowInformation& InBasicWindowInform);

public:

	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Tick() override;
	virtual void PumpMessage() override;
	virtual void Show() override;
	virtual void Hide() override;

	friend FWindow* CreatePlatformWindow(const FBasicWindowInformation& InBasicWindowInform);

private:
	WNDCLASSEXW WindowClass;
	FString WindowClassName;

	HWND hWnd;
};