#include "Unit.hpp"
#include "drawing.hpp"
#include<SDL.h>
#pragma once 

class TNT: public Unit{//TNT is inheriting from unit class
    int frame = 0;//setting frames to change the src rect values later
    bool hit = false;// this cehcks if tnt hits a tank at any given instance or not.
public:
    // add the move function here as well.
    void move();//the move function is defined here
    SDL_Rect getcoords();//this return the cordinates of TNT at a particular instance of falling
    void delete_TNT(int,int); // this deletes TNT as soon as it hits a tank
    TNT(); //default constructor
    TNT(int x, int y);   // parametrized constructor
    bool blast_it(); //it return hit that tells if collision has taken place or not.
};