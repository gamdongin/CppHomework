#include <iostream>
#include "deepl_api.h"

int main() {
    std::string text;

    std::cout << "번역할 문장 입력: ";
    std::getline(std::cin, text);

    std::cout << translateWithDeepL(text, "eng") << std::endl;

    return 0;
}