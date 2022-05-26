#include <iostream>
#include "Unit.hpp"
using namespace std;
#pragma once 
class Weapons:public Unit{

    public:
        Weapons(SDL_Rect src_, SDL_Rect mover_);
        Weapons();
        virtual void move()=0;
};