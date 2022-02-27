// moniBrightness.h - Contains declarations of the functions in moniBrightness.cpp
#pragma once

#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )


extern "C" DllExport void gethMonitor(PHYSICAL_MONITOR* moni_array);

extern "C" DllExport DWORD getBrightness(DWORD* min_brightness, DWORD* cur_brightness, DWORD* max_brightness);

extern "C" DllExport DWORD setBrightness(DWORD new_brightness);