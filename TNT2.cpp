#include "TNT2.hpp"
// firecracker implementation will go here.
#include "drawing.hpp"
#pragma once 

#include "game.hpp"
Game temp_obj_5;

SDL_Rect TNT2::getcoords()
{//this return the moverect of TNT tod etct collision
    return moverRect;
}

bool TNT2::blast_it()
{
    return hit;// the bool variable hit to detect collision
}

void TNT2::delete_TNT2(int x, int y)//the instance Tnt collides, it will be deleted
{
    moverRect = {x, y, 150, 150};
    if (hit == false)
    {
        temp_obj_5.play_collision_sound();//sound for collision is been played.
        hit = true;
        srcRect = {227, 1301, 123, 134};//as soon as collision takes place the src rect changes to that of explosion effect
    }
    else
    {//these frames sets the explosion effect by extracting different src rect values.
        if (frame == 0)
        { 
            srcRect = {404, 1267, 165, 180};
            frame = 1; // the state is resetted and the process repeats
        }

        else if (frame == 1)
        { 
            srcRect = {11, 1470, 181, 178};
            frame = 2; // the state is resetted and the process repeats
        }
        else if (frame == 2)
        { 
            srcRect = {0, 0, 0, 0};
            //the explosion effect will now disappear
        }
    }
}

void TNT2::move()
{
    moverRect.y += 10;
    //TNT is simply falling from sky vertically
}

TNT2::TNT2(){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {1067,498,66,32};
    moverRect = {30, 40, 40, 20}; //deafult constructor
}

TNT2::TNT2(int x, int y){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {1067,498,66,32};
    moverRect = {x, y, 40, 20};//parametruzed constructor
}

