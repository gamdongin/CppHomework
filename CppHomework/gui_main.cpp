#include <Windows.h>
#include <string>
#include "captureAndOCR.h"
#include "deepl_api.h"
#include "textCache.h"

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

std::string deeplAPI = "";
std::string ocrLanguage = "eng";

#define IDC_BTN_TRANSLATE 1001
#define IDC_EDIT_OCR 1002
#define IDC_EDIT_TRANSLATED 1003
#define IDC_EDIT_API 1004
#define IDC_BTN_SAVE_API 1005
#define IDC_RADIO_ENG 1006
#define IDC_RADIO_JPN 1007

HWND hEditOCR;
HWND hEditTranslated;
HWND hEditAPI;

std::wstring Utf8ToWstring(const std::string& str);
std::string WstringToUtf8(const std::wstring& wstr);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE: 
    {
        CreateWindowW(L"BUTTON", L"번역 시작", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 95, 120, 35, hwnd, (HMENU)IDC_BTN_TRANSLATE, nullptr, nullptr);

        CreateWindowW(L"STATIC", L"DeepL API 키:", WS_CHILD | WS_VISIBLE, 20, 20, 100, 25, hwnd, nullptr, nullptr, nullptr);
        CreateWindowW(L"BUTTON", L"API 저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 510, 20, 100, 25, hwnd, (HMENU)IDC_BTN_SAVE_API, nullptr, nullptr);

        hEditAPI = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 120, 20, 380, 25, hwnd, (HMENU)IDC_EDIT_API, nullptr, nullptr);

        hEditOCR = CreateWindowW(L"EDIT", L"OCR", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
            20, 145, 640, 140, hwnd, (HMENU)IDC_EDIT_OCR, nullptr, nullptr);
        hEditTranslated = CreateWindowW(L"EDIT", L"번역", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
            20, 310, 640, 140, hwnd, (HMENU)IDC_EDIT_TRANSLATED, nullptr, nullptr);

        CheckRadioButton(hwnd, IDC_RADIO_ENG, IDC_RADIO_JPN, IDC_RADIO_ENG);
        CreateWindowW(L"STATIC", L"OCR 언어:", WS_CHILD | WS_VISIBLE, 20, 60, 80, 25, hwnd, nullptr, nullptr, nullptr);
        CreateWindowW(L"BUTTON", L"영어", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 100, 60, 70, 25, hwnd, (HMENU)IDC_RADIO_ENG, nullptr, nullptr);
        CreateWindowW(L"BUTTON", L"일본어", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 180, 60, 90, 25, hwnd, (HMENU)IDC_RADIO_JPN, nullptr, nullptr);

        return 0;
    }

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDC_BTN_SAVE_API)
        {
            wchar_t buffer[512];
            GetWindowTextW(hEditAPI, buffer, 512);

            deeplAPI = WstringToUtf8(buffer);

            MessageBoxW(hwnd, L"API 키가 저장되었습니다.", L"확인", MB_OK);
            return 0;
        }

        if (LOWORD(wParam) == IDC_RADIO_ENG)
        {
            ocrLanguage = "eng";
            return 0;
        }

        if (LOWORD(wParam) == IDC_RADIO_JPN)
        {
            ocrLanguage = "jpn";
            return 0;
        }

        if (LOWORD(wParam) == IDC_BTN_TRANSLATE)
        {
            ShowWindow(hwnd, SW_MINIMIZE);
            std::string ocrText = captureAndOCR(ocrLanguage);

            ShowWindow(hwnd, SW_RESTORE);
            SetForegroundWindow(hwnd);

            if (ocrText.empty())
            {
                SetWindowTextW(hEditOCR, L"OCR 결과가 없습니다.");
                return 0;
            }
            SetWindowTextW(hEditOCR, Utf8ToWstring(ocrText).c_str());
            std::string translated;

            if (findCache(ocrText, translated))
            {
                SetWindowTextW(hEditTranslated, Utf8ToWstring(translated).c_str());
            }
            else
            {
                translated = translateWithDeepL(ocrText, "KO", deeplAPI);
                saveCache(ocrText, translated);
                SetWindowTextW(hEditTranslated, Utf8ToWstring(translated).c_str());
            }
        }

        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    const wchar_t CLASS_NAME[] = L"ScreenTranslatorWindow";

    initializeCache();

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"화면 OCR 번역기", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 500, nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};

    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return 0;
}

std::wstring Utf8ToWstring(const std::string& str)
{
    if (str.empty())
        return L"";

    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);

    std::wstring result(size, L'\0');

    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);

    if (!result.empty() && result.back() == L'\0')
        result.pop_back();

    return result;
}

std::string WstringToUtf8(const std::wstring& wstr)
{
    if (wstr.empty())
        return "";

    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);

    std::string result(size, '\0');

    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], size, nullptr, nullptr);

    if (!result.empty() && result.back() == '\0')
        result.pop_back();

    return result;
}