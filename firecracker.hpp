#include "Unit.hpp"
#include "drawing.hpp"
#include<SDL.h>
#pragma once 

class firecracker: public Unit{//inheriting form unit class
    int frame = 0;
    bool hit = false;
public:
    // add the move function here as well, functionalities explained in cpp file
    void move();
    SDL_Rect getcoords();
    void delete_firecracker(int, int);
    firecracker(); 
    firecracker(int x, int y);  
    bool blast_it();
};