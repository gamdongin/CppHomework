#include <iostream>
using namespace std;

#include <windows.h>
#include <limits>
#include <gdiplus.h>

#include "captureAndOCR.h"
#include "deepl_api.h"

#pragma comment(lib, "gdiplus.lib")

string runTranc(const string& deeplAPI)
{
    int choice;
    string lang;
    string text;
    string tranc_text;

    Gdiplus::GdiplusStartupInput gdiplusInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup(
        &gdiplusToken,
        &gdiplusInput,
        NULL
    );


    while (true) {
        cout << u8"OCR 언어를 선택하세요.\n" << u8"1. 영어\n" << u8"2. 일본어\n" << u8"0. 종료\n" << u8"선택: ";
        cin >> choice;
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        if (choice == 1) {
            cout << u8"영어로 OCR을 실행합니다..\n";
            lang = "eng";
        }
        else if (choice == 2) {
            cout << u8"일본어로 OCR을 실행합니다..\n";
            lang = "jpn";
        }
        else if (choice == 0) {
            cout << u8"종료합니다.\n";
            break;
        }
        else {
            cout << u8"잘못된 선택입니다.\n";
            continue;
        }

        while (true) {
            cout << u8"캡쳐를 시작하려면 1을 누르세요.\n" << u8"1. 캡쳐시작\n" << u8"2. OCR 선택\n" << u8"0. 종료\n" << u8"선택: ";
            cin >> choice;
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            if (choice == 1) {

                text = captureAndOCR(lang);

                if (text.empty())
                {
                    cout << u8"OCR 결과가 비어 있습니다.\n";
                    continue;
                }

                // 번역 결과
                tranc_text = translateWithDeepL(text, "KO", deeplAPI);
                cout << tranc_text << endl;
            }
            else if (choice == 2) {
                cout << u8"OCR을 선택합니다..\n";
                break;
            }
            else if (choice == 0) {
                cout << u8"종료합니다.\n";
                Gdiplus::GdiplusShutdown(gdiplusToken);
                return text;

            }
            else {
                cout << u8"잘못된 선택입니다.\n";
                continue;
            }
        }
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return text;
}
