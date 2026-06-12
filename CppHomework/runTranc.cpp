#include <iostream>

#include <windows.h>
#include <gdiplus.h>

#include "captureAndOCR.h"
#include "deepl_api.h"

#include "MainMenu.h"

#pragma comment(lib, "gdiplus.lib")

std::string runTranc(std::string deeplAPI)
{
    std::string text;

    MainMenu mainmenu;
    mainmenu.firstSetting(deeplAPI);
    mainmenu.run();

    return text;
}
