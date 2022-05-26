#include <SDL.h>
#pragma once
#include "drawing.hpp"
#include <iostream>
using namespace std;
class life
{
    SDL_Rect srcRect, moverRect;
    int frame = 0;
    char left_or_right;
    int times = 0;
public:
    // all fuctionalities are explained in cpp
    void draw();
    void health_update(int tank_no);
    char get_heart_char();
    void operator--();
    void operator--(int);
    void delete_right_heart(int);
    void delete_left_heart(int);
    life(char c, SDL_Rect srcRect1, int x, int y);
    SDL_Rect getcoords();
    void update_times(int t);
};
