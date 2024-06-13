#pragma once

#if _WIN32
	#define BUILD_DEBUG _DEBUG
	#define BUILD_RELEASE !BUILD_DEBUG
#endif

// Select pointage SharedLib or StaticLib default is SharedLib
// If you change this, need change configure on solution's settings - "Configuration Properites" 
// Pointage configuration must change into 'Static' configuration
#define POINTAGE_SHARED
