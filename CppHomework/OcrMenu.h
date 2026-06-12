#pragma once
#include "BaseMenu.h"
#include <iostream>

class OcrMenu : public BaseMenu
{
private:
    void show() override;
    int executeChoice(int choice) override;
    void selectEnglish();
    void selectJapanese();
};