#pragma once

class FEngine
{
public:
	void Initialize();
	void ShutDown();

	int Tick();

private:
	void PumpMessages();
	bool bInitialized = false;

	class FWindow* MainWindow;
	FArray<FWindow*> Windows;
};

extern FEngine GEngine;