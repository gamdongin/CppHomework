#pragma once
#include <Windows.h>

HWND getCurrentWindow();
void minimizeWindow(HWND hwnd);
void restoreWindow(HWND hwnd);