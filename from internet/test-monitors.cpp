#include <Windows.h>
#include <iostream>
#include <vector>
#include <cstdio>

std::wstring getMonitorName(HMONITOR monitor) {
    MONITORINFOEXW info;
    info.cbSize = sizeof(info);
    GetMonitorInfoW(monitor, &info);

    UINT32 requiredPaths, requiredModes;
    GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &requiredPaths, &requiredModes);
    std::vector<DISPLAYCONFIG_PATH_INFO> paths(requiredPaths);
    std::vector<DISPLAYCONFIG_MODE_INFO> modes(requiredModes);
    QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &requiredPaths, paths.data(), &requiredModes, modes.data(), nullptr);

    for (auto& p : paths) {
        DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
        sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
        sourceName.header.size = sizeof(sourceName);
        sourceName.header.adapterId = p.sourceInfo.adapterId;
        sourceName.header.id = p.sourceInfo.id;
        DisplayConfigGetDeviceInfo(&sourceName.header);
        if (wcscmp(info.szDevice, sourceName.viewGdiDeviceName) == 0) {
            DISPLAYCONFIG_TARGET_DEVICE_NAME name;
            name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            name.header.size = sizeof(name);
            name.header.adapterId = p.sourceInfo.adapterId;
            name.header.id = p.targetInfo.id;
            DisplayConfigGetDeviceInfo(&name.header);
            return std::wstring(name.monitorFriendlyDeviceName);
        }
    }
    return L"";
}


BOOL CALLBACK MyInfoEnumProc(
    HMONITOR hMonitor,
    HDC hdcMonitor,
    LPRECT lprcMonitor,
    LPARAM dwData
)
{
    MONITORINFOEX mi;
    ZeroMemory(&mi, sizeof(mi));
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);
    wprintf(L"DisplayDevice: %s\n", mi.szDevice);

    std::wcout << L"Name: " << getMonitorName(hMonitor) << L"\n";
    return TRUE;
}

int main()
{
    printf("\n\nEnumDisplayDevices\n\n\n");

    DISPLAY_DEVICE dd;
    ZeroMemory(&dd, sizeof(dd));
    dd.cb = sizeof(dd);
    for (int i = 0; EnumDisplayDevices(NULL, i, &dd, 0); i++)
    {
        wprintf(L"\n\nDevice %d:", i);
        wprintf(L"\n    DeviceName:   '%s'", dd.DeviceName);
        wprintf(L"\n    DeviceString: '%s'", dd.DeviceString);
        wprintf(L"\n    StateFlags:   %s%s%s%s%s",
            ((dd.StateFlags &
                DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) ?
                L"desktop " : L""),
            ((dd.StateFlags &
                DISPLAY_DEVICE_PRIMARY_DEVICE) ?
                L"primary " : L""),
            ((dd.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE) ?
                L"vga " : L""),
            ((dd.StateFlags &
                DISPLAY_DEVICE_MULTI_DRIVER) ?
                L"multi " : L""),
            ((dd.StateFlags &
                DISPLAY_DEVICE_MIRRORING_DRIVER) ?
                L"mirror " : L""));

        // Get more info about the device
        DISPLAY_DEVICE dd2;
        ZeroMemory(&dd2, sizeof(dd2));
        dd2.cb = sizeof(dd2);
        EnumDisplayDevices(dd.DeviceName, 0, &dd2, 0);
        wprintf(L"\n    DeviceID: '%s'", dd2.DeviceID);
        wprintf(L"\n    Monitor Name: '%s'", dd2.DeviceString);
    }

    printf("\n\n\nEnumDisplayMonitors\n\n\n");

    EnumDisplayMonitors(NULL, NULL, MyInfoEnumProc, 0);


    return 0;
}