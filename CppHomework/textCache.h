#pragma once
#include <string>

void initializeCache();

bool findCache(
    const std::string& original,
    std::string& translated
);

void saveCache(
    const std::string& original,
    const std::string& translated
);