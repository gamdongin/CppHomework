#include "TranslateMenu.h"
#include <iostream>
#include <string>

#include "captureAndOCR.h"
#include "deepl_api.h"
#include "windowControl.h"
#include "textCache.h"

void TranslateMenu::show() {
    std::cout << u8"선택하세요.\n" << u8"1. 캡쳐 및 번역 시작\n" << u8"0. 주 메뉴\n" << u8"선택: ";
    numChoice = 1;
}
int TranslateMenu::executeChoice(int choice) {
    switch (choice) {
    case 1:
        startTranslation();
        return 1;
    default:
        std::cout << "menu choice eorror";
        return -1;
    }
}

void TranslateMenu::startTranslation() {

    HWND hwnd = getCurrentWindow();
    minimizeWindow(hwnd);

    std::string tranc_text;
    std::string ocrText = captureAndOCR(ocrLanguage);
    std::string translated;

    restoreWindow(hwnd);

    if (ocrText.empty())
    {
        std::cout << u8"OCR 결과가 비어 있습니다.\n";
        // 이거 때문에 captureAndOCR 에 못 넣음
        return;
    }

    if (findCache(ocrText, translated))
    {
        std::cout << u8"\n===== 캐시 번역 결과 =====\n";
        std::cout << translated << "\n";
        return;
    }

    tranc_text = translateWithDeepL(ocrText, "KO", deeplAPI);
    saveCache(ocrText, tranc_text);
    std::cout << tranc_text << std::endl;
}