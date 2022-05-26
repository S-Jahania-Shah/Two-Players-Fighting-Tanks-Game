#include "firecracker.hpp"
// firecracker implementation will go here.
#include "drawing.hpp"
#pragma once 
#include "game.hpp"
Game temp_obj_1;

bool firecracker::blast_it()//if firecracker has collision or not
{
    return hit;
}

SDL_Rect firecracker::getcoords(){//returning the moverect of firecracker
    return moverRect;
}

void firecracker::delete_firecracker(int x, int y)
{//based on the collisio, firecrcaker src will be erased and explosion src rect will be used.
    moverRect = {x, y, 150, 150};
    if (hit == false)
    {
        temp_obj_1.play_collision_sound();//sound upon collision
        hit = true;//hit or collision took place
        srcRect = {227, 1301, 123, 134};
    }
    else
    {
        if (frame == 0)
        { 
            srcRect = {404, 1267, 165, 180};
            frame = 1; 
        }

        else if (frame == 1)
        { 
            srcRect = {11, 1470, 181, 178};
            frame = 2; 
        }
        else if (frame == 2)
        {//then finally the explosion effect also vanishes away.
            srcRect = {0, 0, 0, 0};
        }
    }
}

void firecracker::move()
{    
    moverRect.y += 10;   //simply fall vertically from sky
}

firecracker::firecracker(){//default constructor
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {1238,485,40, 20};
    moverRect = {30, 40, 40, 20};
}

firecracker::firecracker(int x, int y){//parametrized constructor
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {1238,485,40,50};
    moverRect = {x, y, 40, 20};
}

