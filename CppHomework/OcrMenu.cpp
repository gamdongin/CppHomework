#include "OcrMenu.h"
#include <iostream>


void OcrMenu::show() {
    std::cout << u8"OCR 언어를 선택하세요.\n" << u8"1. 영어\n" << u8"2. 일본어\n" << u8"0. 주 메뉴\n" << u8"선택: ";
    numChoice = 2;
}

int OcrMenu::executeChoice(int choice) {
    switch (choice) {
    case 1:
        selectEnglish();
        return 1;
    case 2:
        selectJapanese();
        return 1;
    default:
        std::cout << "menu choice eorror";
        return -1;
    }
}
void OcrMenu::selectEnglish() {
    ocrLanguage = "eng";
}
void OcrMenu::selectJapanese() {
    ocrLanguage = "jpn";
}