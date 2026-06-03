#include "giveOCR.h"
#include <iostream>
#include <string>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

// 위 두 헤더가 인식이 안 되면

//setup.bat 를 더블 클릭해 실행 하십시오.
//작업완료까지 15분 정도 걸립니다.

std::string giveOCR(const char* imagePath, const char* lang)
{
    tesseract::TessBaseAPI ocr;

    const char* tessdataPath = "./tessdata/";

    if (ocr.Init("./tessdata/", lang))
    {
        std::cout << "OCR 초기화 실패\n";
        return "===============================";
    }

    Pix* image = pixRead(imagePath);

    if (!image)
    {
        std::cout << "이미지 로드 실패\n";
        ocr.End();
        return "===============================";
    }

    ocr.SetImage(image);

    char* text = ocr.GetUTF8Text();

    std::cout << "\n===== OCR 결과 =====\n";
    std::cout << text << std::endl;
    std::cout << "====================\n";

    delete[] text;
    pixDestroy(&image);
    ocr.End();

	return text;
}