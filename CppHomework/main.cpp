#include <iostream>
#include "MainMenu.h"
#include "textCache.h"
using namespace std;

#include <windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Gdiplus::GdiplusStartupInput gdiplusInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup(
        &gdiplusToken,
        &gdiplusInput,
        NULL
    );
//  =   =   =   =   =   =   =   =   =   =   =   =   =   =
    string firstDeeplAPI;
    cout << u8"DeepL API 키 입력: ";
    cin >> firstDeeplAPI;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    initializeCache();
    MainMenu mainmenu;
    mainmenu.firstSetting(firstDeeplAPI);
    mainmenu.run();
 //  =   =   =   =   =   =   =   =   =   =   =   =   =   =
    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 0;
}