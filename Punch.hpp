#include<SDL.h>
#pragma once 
#include "drawing.hpp"
#include "Weapons.hpp"

class Punch: public Weapons{//inheriting publically from weapon class
    // declaring variables
    int frame = 0;
    char left_or_right;
    bool hit  = false;//initially no collision has taken place
    
    public:
        // calling the constructors, draw and move functions all explanation is done in cpp file
        void move();
        Punch(int x, int y,char tank_pos); 
        char get_tank_char();
        bool blast_it();
        SDL_Rect getcoords();
        void delete_Punch();
};
