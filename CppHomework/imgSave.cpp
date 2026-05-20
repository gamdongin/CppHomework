#include "imgChap.h"
#include "imgSave.h"
#include <windows.h>
#include <gdiplus.h>
#include <iostream>

#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0;
    UINT size = 0;

    GetImageEncodersSize(&num, &size);

    if (size == 0)
    {
        return -1;
    }

    ImageCodecInfo* pImageCodecInfo =
        (ImageCodecInfo*)malloc(size);

    if (pImageCodecInfo == NULL)
    {
        return -1;
    }

    GetImageEncoders(
        num,
        size,
        pImageCodecInfo
    );

    for (UINT i = 0; i < num; i++)
    {
        if (wcscmp(
            pImageCodecInfo[i].MimeType,
            format
        ) == 0)
        {
            *pClsid =
                pImageCodecInfo[i].Clsid;

            free(pImageCodecInfo);
            return i;
        }
    }

    free(pImageCodecInfo);
    return -1;
}

bool saveClipboardImage(const wchar_t* filename)
{
    if (!OpenClipboard(NULL))
    {
        return false;
    }

    HANDLE hData =
        GetClipboardData(CF_BITMAP);

    if (hData == NULL)
    {
        CloseClipboard();
        return false;
    }

    HBITMAP hBitmap =
        (HBITMAP)hData;

    Bitmap bitmap(hBitmap, NULL);

    CLSID pngClsid;

    if (GetEncoderClsid(
        L"image/png",
        &pngClsid
    ) == -1)
    {
        CloseClipboard();
        return false;
    }

    Status status =
        bitmap.Save(
            filename,
            &pngClsid,
            NULL
        );

    CloseClipboard();

    return status == Ok;
}

bool startScreenCaptureAndSave(const wchar_t* filename)
{
    startScreenClip();

    std::cout << "캡쳐할 영역을 선택한 뒤 Enter를 누르세요.\n";
    std::cin.get();

    return saveClipboardImage(filename);
}