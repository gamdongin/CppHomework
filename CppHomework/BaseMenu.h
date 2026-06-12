#pragma once
#include <string>

class BaseMenu
{
public:
    void run();                     // 메뉴 실행
protected:
    virtual void show() = 0;        // 메뉴 출력
    virtual int executeChoice(int choice) = 0;    // 정수에 맞는 함수 실행
    int inputChoice();              // 선택 입력
    int numChoice;
    static std::string deeplAPI;
    static std::string ocrLanguage;
};

//MainMenu
//0. 종료
//1. API 입력
//2. OCR 선택
//3. 번역 시작
//
//ApiMenu
//0. 이전 메뉴 (주메뉴)
//1. API 입력 시작
//
//OCRMenu
//0. 이전 메뉴 (주메뉴)
//1. 영어
//2. 일본어
//
//TranslateMenu
//0. 이전 메뉴 (주메뉴)
//1. OCR 시작