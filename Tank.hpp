#include<SDL.h>
#include "drawing.hpp"
#include "Unit.hpp"
#pragma once 

class Tank: public Unit{
    int frame = 0;//tank inheriting from unit class

public:
    // add the move function here as well.
    void move(SDL_Keycode key,int tank_no);
    Tank(); //deafult constructor
    Tank(int x, int y);//parametrized constructor
    Tank(int tank_no,SDL_Rect srcRect1, int x, int y);//parametrized constructor
    SDL_Rect getcoords();//return the mover rect of tank
    
};
