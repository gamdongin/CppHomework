#include <iostream>
#include "deepl_api.h"
using namespace std;

int main() {

    string text;
	string deeplAPI;

	cout << "DeepL API 키 입력: ";
    cin >> deeplAPI;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    cout << "번역할 문장 입력: ";
    getline(cin, text);

    cout << translateWithDeepL(text, "EN", deeplAPI) << endl;

    return 0;
}