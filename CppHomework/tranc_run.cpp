#include <iostream>
using namespace std;

#include <windows.h>
#include <gdiplus.h>

#include "imgSave.h"
#include "giveOCR.h"

#pragma comment(lib, "gdiplus.lib")

int main()
{
    Gdiplus::GdiplusStartupInput gdiplusInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup(
        &gdiplusToken,
        &gdiplusInput,
        NULL
    );

    const wchar_t* savePathW = L"capture.png";
    const char* savePath = "capture.png";

    cout << "캡쳐 버튼 실행 중...\n";

    if (!startScreenCaptureAndSave(savePathW))
    {
        cout << "캡쳐 이미지 저장 실패\n";
        Gdiplus::GdiplusShutdown(gdiplusToken);
        return -1;
    }

    cout << "캡쳐 이미지 저장 완료\n";

    giveOCR(savePath);

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 0;
}
