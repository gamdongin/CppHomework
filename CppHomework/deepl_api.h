#pragma once
#include <string>

std::string translateWithDeepL(
    const std::string& text,
    const std::string& targetLang,
    const std::string API_KEY = u8"여기에_API_키"
);