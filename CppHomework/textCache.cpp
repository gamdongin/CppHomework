#include "textCache.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static const std::string CACHE_FILE = "text_cache.json";

void initializeCache()
{
    std::ifstream inFile(CACHE_FILE);
    if (!inFile.good())
    {
        std::ofstream outFile(CACHE_FILE);
        outFile << "{}";
        outFile.close();
    }
}

bool findCache(const std::string& original, std::string& translated)
{
    std::ifstream inFile(CACHE_FILE);
    if (!inFile.is_open()) { return false; }
    json cache;
    try { inFile >> cache; }
    catch (...) { return false; }

    if (cache.contains(original))
    {
        translated = cache[original].get<std::string>();
        return true;
    }
    return false;
}

void saveCache(const std::string& original, const std::string& translated)
{
    json cache;
    std::ifstream inFile(CACHE_FILE);

    if (inFile.is_open())
    {
        try { inFile >> cache; }
        catch (...) { cache = json::object(); }
    }

    cache[original] = translated;
    std::ofstream outFile(CACHE_FILE);

    if (!outFile.is_open())
    {
        std::cout << u8"캐시 파일 저장 실패\n";
        return;
    }
    outFile << cache.dump(4);
}