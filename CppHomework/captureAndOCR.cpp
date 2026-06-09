#include <iostream>
#include <string>

#include "captureAndOCR.h"
#include "imgSave.h"
#include "giveOCR.h"

using namespace std;

string captureAndOCR(const string& lang) {
    cout << u8"캡쳐를 시작합니다..\n";

    const wchar_t* savePathW = L"capture.png";
    const char* savePath = "capture.png";

    cout << u8"캡쳐 버튼 실행 중...\n";

    if (!startScreenCaptureAndSave(savePathW))
    {
        cout << u8"캡쳐 이미지 저장 실패\n";
        return "";
    }

    cout << u8"캡쳐 이미지 저장 완료\n";

    // OCR 결과
    string text = giveOCR(savePath, lang.c_str());

    return text;
}