#include "windowControl.h"

HWND getCurrentWindow()
{
    return GetConsoleWindow();
}

void minimizeWindow(HWND hwnd)
{
    if (hwnd != nullptr)
        ShowWindow(hwnd, SW_MINIMIZE);
}

void restoreWindow(HWND hwnd)
{
    if (hwnd != nullptr)
    {
        ShowWindow(hwnd, SW_RESTORE);
        SetForegroundWindow(hwnd);
    }
}