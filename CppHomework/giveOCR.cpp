#include "giveOCR.h"
#include <iostream>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

// 위 두 헤더가 인식이 안 되면 cmd 에서
//
// git clone https://github.com/microsoft/vcpkg
// cd vcpkg
// bootstrap-vcpkg.bat
// vcpkg install tesseract:x64-windows
// vcpkg integrate install

// 각각 순서대로 시행하면 됩니다.

// CppHomework 을 우 클릭 후 빌드 이벤트 찾아서 빌드 후 이벤트에 아래 명령어를 입력하면 됩니다.
// xcopy /E /I /Y "$(ProjectDir)tessdata" "$(OutDir)tessdata"

void giveOCR(const char* imagePath)
{
    tesseract::TessBaseAPI ocr;

    const char* tessdataPath = "./tessdata/";

    if (ocr.Init(tessdataPath, "jpn+eng"))
    {
        std::cout << "OCR 초기화 실패\n";
        return;
    }

    Pix* image = pixRead(imagePath);

    if (!image)
    {
        std::cout << "이미지 로드 실패\n";
        ocr.End();
        return;
    }

    ocr.SetImage(image);

    char* text = ocr.GetUTF8Text();

    std::cout << "\n===== OCR 결과 =====\n";
    std::cout << text << std::endl;
    std::cout << "====================\n";

    delete[] text;
    pixDestroy(&image);
    ocr.End();
}