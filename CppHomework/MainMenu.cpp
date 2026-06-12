#include "MainMenu.h"
#include <iostream>

#include "OcrMenu.h"
#include "ApiMenu.h"
#include "TranslateMenu.h"

void MainMenu::show() {
    std::cout << u8"선택하세요.\n" << u8"1. 번역 시작\n" << u8"2. API 메뉴\n" << u8"3. OCR 메뉴\n" << u8"0. 종료\n" << u8"선택: ";
    numChoice = 3;
}

int MainMenu::executeChoice(int choice) {
    switch (choice) {
    case 1: {
        TranslateMenu translateMenu;
        translateMenu.run();
        break;
    }
    case 2: {
        ApiMenu apimenu;
        apimenu.run();
        break;
    }
    case 3: {
        OcrMenu ocrmenu;
        ocrmenu.run();
        break;
    }
    default:
        std::cout << "menu choice eorror";
        break;
    }
    return 1;
}

void MainMenu::firstSetting(std::string firstDeeplAPI) {
    deeplAPI = firstDeeplAPI;
    ocrLanguage = "eng";
}
