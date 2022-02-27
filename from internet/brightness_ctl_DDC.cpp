// Phys monitor control via DDC/CI or VESA commands
// (David Lowndes)
// From https://social.msdn.microsoft.com/Forums/en-US/5437ddb8-af86-4cf0-8061-798e6601e08e/how-to-control-system-brightness-using-windows-api-?forum=windowsgeneraldevelopmentissues#554b7b7f-0aab-429d-9c36-fd39608979b0

#include <Windows.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#pragma comment( lib, "Dxva2.lib" )

void 
test_brightness()
{

	HWND win_handle = GetDesktopWindow();
	HMONITOR hMon = MonitorFromWindow(win_handle, MONITOR_DEFAULTTOPRIMARY);

	if (hMon != NULL)
	{
		DWORD num_of_monitors;
		BOOL bOK = GetNumberOfPhysicalMonitorsFromHMONITOR(hMon, &num_of_monitors);
		if (bOK)
		{
			LPPHYSICAL_MONITOR pPhysical_monitors = (LPPHYSICAL_MONITOR)malloc(num_of_monitors * sizeof(
				PHYSICAL_MONITOR));
			if (pPhysical_monitors != NULL)
			{
				bOK = GetPhysicalMonitorsFromHMONITOR(hMon, num_of_monitors, pPhysical_monitors);
			}

			HANDLE hMonitor = pPhysical_monitors[0].hPhysicalMonitor;

			DWORD min, cur, max;
			bOK = GetMonitorBrightness(hMonitor, &min, &cur, &max);
			if (!bOK)
			{
				DWORD Err = GetLastError();
				Err = Err;
			}
			else
			{
				// Check altering the brightness
				bOK = SetMonitorBrightness(hMonitor, cur / 32);

				if (bOK)
				{
					bOK = SetMonitorBrightness(hMonitor, cur);
				}
			}
		}
	}
}