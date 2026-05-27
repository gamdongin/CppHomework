#include <iostream>
using namespace std;

#include <windows.h>
#include <limits>
#include <gdiplus.h>

#include "imgSave.h"
#include "giveOCR.h"

#pragma comment(lib, "gdiplus.lib")

int main()
{
    int choice;
    string lang;
    cout << "OCR 언어를 선택하세요.\n";
    cout << "1. 영어\n";
    cout << "2. 일본어\n";
    cout << "선택: ";
    cin >> choice;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    if (choice == 1) {
        lang = "eng";
    }
    else if (choice == 2) {
        lang = "jpn";
    }
    else {
        cout << "잘못된 선택입니다. 일본어로 실행합니다.\n";
        lang = "jpn";
    }

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

    giveOCR(savePath, lang.c_str());

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 0;
}
