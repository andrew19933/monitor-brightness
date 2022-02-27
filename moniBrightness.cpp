// moniBrightness.cpp
// contains functions that can get and set the monitor brightness
//
// Written by Andrew Ballin -- April 2021
//
// TODO: if setBrightness goes out of bounds, have it set to nearest valid brightness

#include <iostream>
#include <Windows.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include "moniBrightness.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Dxva2.lib")

// gets the hMonitor thing to the monitor we want to adjust
void gethMonitor(PHYSICAL_MONITOR* moni_array)
{
	HWND win_handle = GetDesktopWindow(); // assume we want to modify monitor
										  // where desktop is located (not quite sure what this means in full detail)
	//std::cout << "desktop window handle is " << win_handle << " aka " << int(win_handle) << std::endl;
	
	HMONITOR moni_handle = MonitorFromWindow(win_handle, MONITOR_DEFAULTTONULL);
	//std::cout << "monitor handle is " << moni_handle << " aka " << int(moni_handle) << std::endl;
	
	DWORD num_monis;
	
	GetNumberOfPhysicalMonitorsFromHMONITOR(moni_handle, &num_monis);
	//std::cout << "number of physical monitors is " << num_monis << std::endl;
	
	if(!GetPhysicalMonitorsFromHMONITOR(moni_handle, num_monis, moni_array))
	{
		std::cout << "error getting hMonitor" << std::endl;
		exit(1);
	}
}

// gets the min, current, and max brightness of the monitor
DWORD getBrightness(DWORD* min_brightness, DWORD* cur_brightness, DWORD* max_brightness)
{
	PHYSICAL_MONITOR moni_array;
	
	gethMonitor(&moni_array);
	
	if(GetMonitorBrightness(moni_array.hPhysicalMonitor, min_brightness, cur_brightness, max_brightness))
	{
		//std::cout << "minimum brightness is " << min_brightness << std::endl;
		//std::cout << "current brightness is " << cur_brightness << std::endl;
		//std::cout << "maximum brightness is " << max_brightness << std::endl;
		return *cur_brightness;
	}
	else
	{
		std::cout << "error in GetMonitorBrightness :(" << std::endl;
		exit(1);
	}
	
	return -1;
}


// sets the monitor's brightness to a particular value
DWORD setBrightness(DWORD new_brightness)
{	
	PHYSICAL_MONITOR moni_array;
	
	gethMonitor(&moni_array);
	
	DWORD min_brightness;
	DWORD cur_brightness;
	DWORD max_brightness;
	
	getBrightness(&min_brightness, &cur_brightness, &max_brightness);
	
	// test if new_brightness is in valid range
	if(new_brightness < min_brightness || new_brightness > max_brightness)
	{
		std::cout << "requested brightness is too high or too low" << std::endl;
		return cur_brightness;
	}
	else
	{
		if(SetMonitorBrightness(moni_array.hPhysicalMonitor, new_brightness))
		{
			//std::cout << "minimum brightness is " << min_brightness << std::endl;
			//std::cout << "current brightness is " << cur_brightness << std::endl;
			//std::cout << "maximum brightness is " << max_brightness << std::endl;
			return new_brightness;
		}
		else
		{
			std::cout << "error in SetMonitorBrightness :(" << std::endl;
			exit(1);
		}
	}
	
	return -1;
}


int main()
{
	//DWORD min_brightness;
	//DWORD cur_brightness;
	//DWORD max_brightness;
	
	//getBrightness(&min_brightness, &cur_brightness, &max_brightness);
	//std::cout << "minimum brightness is " << min_brightness << std::endl;
	//std::cout << "current brightness is " << cur_brightness << std::endl;
	//std::cout << "maximum brightness is " << max_brightness << std::endl;

	//setBrightness(30);
	
	return 0;
}