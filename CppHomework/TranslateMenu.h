#pragma once
#include "BaseMenu.h"
#include <iostream>

class TranslateMenu : public BaseMenu
{
private:
    void show() override;
    int executeChoice(int choice) override;
    void startTranslation();
};