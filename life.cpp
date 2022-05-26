#pragma once
#include "life.hpp"
// Tank implementation will go here.

void life::draw()
{
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect); //  used for drawing the hearts
}
void life::update_times(int t)
{
    times = t;//the times we are updating our health for each tank
}
void life::operator--()//operator overloading is used. based on the times we are changing the src rect of hearts
{
    if (times == 0)
        srcRect = {1018, 1342, 205, 42}; // aik kam heart waly src rect hogae hain ab.
    else if (times == 1)
    {
        srcRect = {1018, 1399, 151, 42};
        moverRect = {40, 20, 120, 40};
    }
    else if (times == 2)
    {
        srcRect = {1016, 1455, 99, 41};
        moverRect = {40, 20, 60, 40};
    }
    else if (times == 3)
    {
        srcRect = {1015, 1511, 46, 40};
        moverRect = {40, 20, 40, 40};
    }
    else
        srcRect = {0, 0, 0, 0};//all hearts have been finished.
}
void life::operator--(int)//operator overloading is used.
{
    if (times == 0)
        srcRect = {1442, 1343, 205, 41}; // aik kam heart waly src rect hogae hain ab.
    else if (times == 1)
    {
        srcRect = {1493, 1393, 153, 40};
        moverRect = {800, 20, 120, 40};
    }
    else if (times == 2)
    {
        srcRect = {1548, 1443, 99, 40};
        moverRect = {800, 20, 60, 40};
    }
    else if (times == 3)
    {
        srcRect = {1602, 1492, 47, 40};
        moverRect = {800, 20, 40, 40};
    }
    else
        srcRect = {0, 0, 0, 0};
    // times += 1;
}
void life::delete_right_heart(int times)
{

    if (times == 0)
        srcRect = {1442, 1343, 205, 41}; // aik kam heart waly src rect hogae hain ab.
    else if (times == 1)
    {
        srcRect = {1493, 1393, 153, 40};
        moverRect = {800, 20, 120, 40};
    }
    else if (times == 2)
    {
        srcRect = {1548, 1443, 99, 40};
        moverRect = {800, 20, 60, 40};
    }
    else if (times == 3)
    {
        srcRect = {1602, 1492, 47, 40};
        moverRect = {800, 20, 40, 40};
    }
    else
        srcRect = {0, 0, 0, 0};
}

void life::delete_left_heart(int times)
{

    if (times == 0)
        srcRect = {1018, 1342, 205, 42}; // aik kam heart waly src rect hogae hain ab.
    else if (times == 1)
    {
        srcRect = {1018, 1399, 151, 42};
        moverRect = {40, 20, 120, 40};
    }
    else if (times == 2)
    {
        srcRect = {1016, 1455, 99, 41};
        moverRect = {40, 20, 60, 40};
    }
    else if (times == 3)
    {
        srcRect = {1015, 1511, 46, 40};
        moverRect = {40, 20, 40, 40};
    }
    else
        srcRect = {0, 0, 0, 0};
}

char life::get_heart_char()
{
    return left_or_right;//heart is of left or right tank
}

SDL_Rect life::getcoords()
{
    return moverRect;//return the moverect of heart
}

life::life(char c, SDL_Rect srcRect1, int x, int y)
{
    srcRect = srcRect1;
    left_or_right = c;//this is parametrized constructor 
    if (c == 'l')
        moverRect = {x, y, 150, 50};
    else if (c == 'r')
        moverRect = {x, y, 150, 50}; // x=800, y=20
    frame = 1;
    times = 0;
}
