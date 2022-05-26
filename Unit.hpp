#pragma once
#include<SDL.h>
#include "drawing.hpp"
#include<vector>
#include<list>
using namespace std;

class Unit{// the parent class. it's attributes srcRect adnd moverRect are used by the child 
            //classes according to unique srcrect and moverRect values
    protected:
        SDL_Rect srcRect, moverRect; // declaring attributes of the SDL's

    public:
        // caling the functions created in the cpp file
        Unit(SDL_Rect src, SDL_Rect mover); //parametrized constructor
        Unit(SDL_Rect src);// parametrized constructor
        Unit();//default constructor
        void draw();
        virtual void move();// this makes the class abstract. each object inheriting  unit class will have its own definition of fly 
                            //function
};