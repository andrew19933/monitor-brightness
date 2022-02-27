// decMoniBrightness.cpp
// decreases the monitor brightness by 10 units
// wrote as a temporary fix until I can get the DLL working with AutoHotkey so I can call functions directly

#include <iostream>
#include <Windows.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Dxva2.lib")


void gethMonitor(PHYSICAL_MONITOR* moni_array)
{
	HWND win_handle = GetDesktopWindow();
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


DWORD setBrightness(DWORD new_brightness)
{	
	PHYSICAL_MONITOR moni_array;
	
	gethMonitor(&moni_array);
	
	DWORD min_brightness;
	DWORD cur_brightness;
	DWORD max_brightness;
	
	getBrightness(&min_brightness, &cur_brightness, &max_brightness);
	
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
	DWORD min_brightness;
	DWORD cur_brightness;
	DWORD max_brightness;
	
	getBrightness(&min_brightness, &cur_brightness, &max_brightness);

	setBrightness(cur_brightness - 10);
	
	return 0;
}