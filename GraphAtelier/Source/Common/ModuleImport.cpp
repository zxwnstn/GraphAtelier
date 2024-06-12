
#if _DEBUG
	#pragma comment(lib, "Binaries/imgui_x64_Debug.lib")
	#pragma comment(lib, "FirstParty/Pointage/Binaries/Pointaged.lib")
#else
	#pragma comment(lib, "Binaries/imgui.lib")
	#pragma comment(lib, "FirstParty/Pointage/Binaries/Pointage.lib")
#endif
