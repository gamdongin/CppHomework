// deepl_api.cpp

#include "deepl_api.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using namespace std;

using json = nlohmann::json;

// ?? 여기에 네 API 키 입력
static const std::string API_KEY =
"여기에_API_키";

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

std::string translateWithDeepL(const std::string& text) {

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
        "&target_lang=KO";

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

        return "JSON PARSE FAILED";
    }
}