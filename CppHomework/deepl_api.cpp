// deepl_api.cpp
// deelp 모듈

#include "deepl_api.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using namespace std;

using json = nlohmann::json;

static size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    void* userp
) {
    ((std::string*)userp)->append(
        (char*)contents,
        size * nmemb
    );

    return size * nmemb;
}

string translateWithDeepL(const string& text, const string& targetLang, const string API_KEY) {

    CURL* curl = curl_easy_init();

    if (!curl)
        return "CURL INIT FAILED";

    std::string response;

    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        "https://api-free.deepl.com/v2/translate"
    );

    // POST 사용
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // UTF-8 문자열 URL 인코딩
    char* escaped = curl_easy_escape(
        curl,
        text.c_str(),
        (int)text.length()
    );

    std::string postFields =
        "text=" + std::string(escaped) +
        "&target_lang=" + targetLang;

    curl_free(escaped);

    curl_easy_setopt(
        curl,
        CURLOPT_POSTFIELDS,
        postFields.c_str()
    );

    // 헤더
    struct curl_slist* headers = nullptr;

    std::string authHeader =
        "Authorization: DeepL-Auth-Key " + API_KEY;

    headers = curl_slist_append(
        headers,
        authHeader.c_str()
    );

    headers = curl_slist_append(
        headers,
        "Content-Type: application/x-www-form-urlencoded"
    );

    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers
    );

    // 응답 받기
    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        WriteCallback
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &response
    );

    CURLcode res = curl_easy_perform(curl);

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    std::cout << "HTTP CODE: " << httpCode << std::endl;
    std::cout << "RAW RESPONSE:\n" << response << std::endl;

    if (res != CURLE_OK) {

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return "REQUEST FAILED";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    // JSON 파싱
    try {

        json j = json::parse(response);

        return j["translations"][0]["text"];

    }
    catch (...) {
        return "JSON PARSE FAILED:\n" + response;
    }
}