#pragma once
#include "BaseMenu.h"
#include <iostream>

class MainMenu : public BaseMenu
{
public:
    void firstSetting(std::string firstDeeplAPI);
private:
    void show() override;
    int executeChoice(int choice) override;
};