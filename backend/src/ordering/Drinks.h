#ifndef DRINKS_H
#define DRINKS_H
#include <iostream>
#include "Menu.h"
#include<vector>
class Drinks: public Menu{
    public:
        std::vector<std::string> getItems() override;
        void displayMenu();
};
#endif