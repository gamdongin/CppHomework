#include <windows.h>
#include <gdiplus.h>

#include "imgChap.h"
#include "giveOCR.h"

#pragma comment(lib, "gdiplus.lib")

int main()
{
    Gdiplus::GdiplusStartupInput input;
    ULONG_PTR token;

    Gdiplus::GdiplusStartup(
        &token,
        &input,
        NULL
    );

    if (
        startScreenCaptureAndSave(
            L"capture.png"))
    {
        giveOCR(
            "capture.png");
    }

    Gdiplus::GdiplusShutdown(
        token);

    return 0;
}
