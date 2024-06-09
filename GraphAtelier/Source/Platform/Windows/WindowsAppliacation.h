#pragma once

class FWindowsApplication
	: public FApplication
{
public:
	FWindowsApplication(HINSTANCE InInstance);

	virtual bool Initialize() override;
	virtual void ShutDown() override;

	virtual void* GetHandle() override;

private:
	HINSTANCE Instance;
};
