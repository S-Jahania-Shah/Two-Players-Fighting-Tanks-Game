#include<SDL.h>
#include "Weapons.hpp"
#include "drawing.hpp"
#pragma once 
class Bullets: public Weapons{
    // declaring variables
    int frame = 0;
    char left_or_right;
    bool hit  = false;
    public:
        // calling the constructors, draw and move functions
        void move();
        Bullets(int x, int y,char tank_pos); 
        SDL_Rect getcoords();
        bool blast_it();
        void delete_bullet();
        char get_tank_char();
};
