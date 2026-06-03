#include <iostream>
#include "deepl_api.h"
using namespace std;

#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string text;
	string deeplAPI;

	cout << u8"DeepL API 키 입력: ";
    cin >> deeplAPI;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    cout << u8"번역할 문장 입력: ";
    getline(cin, text);

    cout << translateWithDeepL(text, "KO", deeplAPI) << endl;

    return 0;
}