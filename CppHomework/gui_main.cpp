#include <Windows.h>
#include <string>
#include "captureAndOCR.h"

#define IDC_BTN_TRANSLATE 1001
#define IDC_EDIT_OCR 1002
#define IDC_EDIT_TRANSLATED 1003

HWND hEditOCR;
HWND hEditTranslated;

std::wstring Utf8ToWstring(const std::string& str);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        CreateWindowW(L"BUTTON", L"번역 시작", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 20, 120, 35, hwnd, (HMENU)IDC_BTN_TRANSLATE, nullptr, nullptr);

        hEditOCR = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
            20, 70, 640, 150, hwnd, (HMENU)IDC_EDIT_OCR, nullptr, nullptr);

        hEditTranslated = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
            20, 250, 640, 180, hwnd, (HMENU)IDC_EDIT_TRANSLATED, nullptr, nullptr);

        return 0;
    }

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDC_BTN_TRANSLATE)
        {
            MessageBoxW(hwnd, L"1. 버튼 클릭됨", L"확인", MB_OK);

            ShowWindow(hwnd, SW_MINIMIZE);

            MessageBoxW(nullptr, L"2. 캡쳐 시작 전", L"확인", MB_OK);

            std::string ocrText = captureAndOCR("eng");

            MessageBoxW(nullptr, L"3. OCR 함수 통과", L"확인", MB_OK);

            ShowWindow(hwnd, SW_RESTORE);
            SetForegroundWindow(hwnd);

            if (ocrText.empty())
            {
                SetWindowTextW(hEditOCR, L"OCR 결과가 없습니다.");
                return 0;
            }

            std::wstring ocrW = Utf8ToWstring(ocrText);
            SetWindowTextW(hEditOCR, ocrW.c_str());
            SetWindowTextW(hEditTranslated, L"번역은 아직 연결 전입니다.");
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
    const wchar_t CLASS_NAME[] = L"ScreenTranslatorWindow";

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