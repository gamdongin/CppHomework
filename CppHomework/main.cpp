#include <iostream>
#include "runTranc.h"
using namespace std;

#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string deeplAPI;
    cout << u8"DeepL API 키 입력: ";
    cin >> deeplAPI;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    runTranc(deeplAPI);

    return 0;
}