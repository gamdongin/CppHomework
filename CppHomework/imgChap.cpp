#include "imgChap.h"
#include <windows.h>
#include <gdiplus.h>
#include <iostream>

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

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

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num, size;

    GetImageEncodersSize(&num, &size);

    ImageCodecInfo* pInfo =
        (ImageCodecInfo*)malloc(size);

    GetImageEncoders(num, size, pInfo);

    for (UINT i = 0; i < num; i++)
    {
        if (wcscmp(pInfo[i].MimeType, format) == 0)
        {
            *pClsid = pInfo[i].Clsid;
            free(pInfo);
            return i;
        }
    }

    free(pInfo);
    return -1;
}

bool saveClipboardImage(const wchar_t* filename)
{
    if (!OpenClipboard(NULL))
        return false;

    HBITMAP hBitmap =
        (HBITMAP)GetClipboardData(CF_BITMAP);

    if (!hBitmap)
    {
        CloseClipboard();
        return false;
    }

    Bitmap bitmap(hBitmap, NULL);

    CLSID pngClsid;
    GetEncoderClsid(
        L"image/png",
        &pngClsid
    );

    bitmap.Save(filename, &pngClsid);

    CloseClipboard();

    return true;
}

bool startScreenCaptureAndSave(const wchar_t* filename)
{
    startScreenClip();

    std::cout
        << "Ä¸ÃÄ ÈÄ Enter...\n";

    std::cin.get();

    return saveClipboardImage(filename);
}