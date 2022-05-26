#include<SDL.h>
#include "drawing.hpp"
#include "Unit.hpp"
#pragma once 
class Crow:public Unit{//inheriting from unit class
    
    int frame = 0;

    public:
    //functionalities explained in cpp file
        void draw();
        void move();
        Crow();
        Crow(int x, int y); 
};
