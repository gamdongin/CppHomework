#pragma once
#include "BaseMenu.h"
#include <iostream>

class ApiMenu : public BaseMenu
{
public:
    void show() override;
private:
    int executeChoice(int choice) override;
    void inputApiKey();
};