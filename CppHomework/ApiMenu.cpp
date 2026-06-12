#include "ApiMenu.h"
#include <iostream>
#include <string>
#include "deepl_api.h"

void ApiMenu::show() {
    std::cout << u8"선택하세요.\n" << u8"1. API 키입력\n" << u8"0. 주 메뉴\n" << u8"선택: ";
    numChoice = 1;
}
int ApiMenu::executeChoice(int choice) {
    switch (choice) {
    case 1:
        inputApiKey();
        return 1;
    default:
        std::cout << "menu choice eorror";
        return -1;
    }
}
void ApiMenu::inputApiKey() {
    std::cout << u8"DeepL API 키 입력: ";
    std::cin >> deeplAPI;   // BaseMenu 에 있는거
    std::cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}