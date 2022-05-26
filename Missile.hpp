#include<SDL.h>
#pragma once 
#include "drawing.hpp"
#include "Weapons.hpp"

class Missile: public Weapons{//inheriting from weapon class
    // declaring variables
    int frame = 0;
    char left_or_right;
    bool hit  = false;//initally no hit has happened
    public:
        // calling the constructors, draw and fly functions explanation is done in cpp 
        void move();
        Missile(int x, int y,char tank_pos); 
        SDL_Rect getcoords();
        bool blast_it();
        void delete_missile();
        char get_tank_char();

};
