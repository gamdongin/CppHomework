#pragma once
#include <string>
using namespace std;

string translateWithDeepL(
    const string& text,
    const string& targetLang,
    const string& API_KEY
);