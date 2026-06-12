#include "BaseMenu.h"
#include <iostream>

std::string BaseMenu::deeplAPI = "";
std::string BaseMenu::ocrLanguage = "eng";
void BaseMenu::run() {

    while (true)
    {
        std::cout << u8"현재 번역할 언어 : " << ocrLanguage << std::endl;
        show();                 // 각 메뉴 함수마다 작성할 거

        int choice = inputChoice();

        if (choice == 0)
            break;

        executeChoice(choice);  // 각 메뉴 함수마다 작성할 거
    }
}
int BaseMenu::inputChoice() {
    int choice;
    while (true)
    {
        std::cin >> choice;
        if (std::cin.fail()) { std::cin.clear(); choice = -1; }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        if (choice >= 0 && choice <= numChoice)
        {
            return choice;
        }
        std::cout << u8"잘못된 선택입니다.\n";
    }
}