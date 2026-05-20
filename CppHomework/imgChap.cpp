#include "imgChap.h"
#include <windows.h>
#include <iostream>

void startScreenClip()
{
    ShellExecuteW(
        NULL,
        L"open",
        L"explorer.exe",
        L"ms-screenclip:",
        NULL,
        SW_SHOWNORMAL
    );
}