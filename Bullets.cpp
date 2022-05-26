#include "Bullets.hpp"
// Missile implementation will go here.
// constructors
#pragma once 
#include "game.hpp"
Game temp_obj;

Bullets::Bullets(int x, int y,char tank_pos){//parametrized constructor
    left_or_right = tank_pos;
    // src coorinates from assets.png file, they have been found using spritecow.com
    if(left_or_right == 'l'){
        srcRect = {819,268,42,36};
    }
    else if(left_or_right == 'r'){
        srcRect = {986,374,43,36};
    }
    moverRect = {x, y, 100, 40};
}

SDL_Rect Bullets::getcoords(){
    return moverRect;
}
// functionalities

char Bullets::get_tank_char()
{
    return left_or_right;
}

bool Bullets::blast_it()
{
    return hit;
}

void Bullets::delete_bullet(){//based on when bullet collides the src rect of bullet will change into that of explosion effect
    if (hit == false){
        temp_obj.play_collision_sound();
        hit = true;
        srcRect={898,57,57,54};
        frame = 6;
        
    }
    else
    {
        if(frame == 6){ 
            srcRect = {763,71,34,30};
            frame = 7;
        }

        else if(frame == 7){ 
            srcRect = {831,64,44,41};
            frame = 8;
        }
        else if(frame == 8){ 
            srcRect = {898,57,57,54};
            frame = 9;
        }
        else if(frame == 9){ 
            srcRect = {968,59,63,58};
            frame = 10;
        }
        else if(frame == 10){ 
            srcRect = {1038,53,65,68};
            frame = 11;
        }
        else if(frame == 11){
            srcRect = {1112,54,63,64};
            frame = 12;
        }
        else if(frame == 12){ 
            srcRect = {1194,64,46,50};
            frame = 13;
        }
        else if(frame == 13){
            srcRect = {1269,69,41,39};
            frame = 14;
        }
        else if(frame == 14){
            srcRect = {0,0,0,0};//the explosion effect also vanishes then
        }
    }
}

void Bullets::move(){
//to move the bullet 
    if(left_or_right == 'l' && hit == false){
        moverRect.x += 15;
        if(frame == 0){// the initial state of the bullet
            srcRect = {819,268,42,36};
            frame = 1; 
        }

        else if(frame == 1){ 
            srcRect = {950,267,44,38};
            frame = 2;
        }

        else if(frame == 2){ 
            srcRect = {1000,271,38,30};
            frame = 3;
        }

        else if(frame == 3){ 
            srcRect = {1051,274,31,23};
            frame = 4;
        }
        else if(frame == 4){ 
            srcRect = {1103,278,23,15};
            frame = 5;
        }
        else if(frame == 5){ 
            srcRect = {1151,281,19,10};
            frame = 6;
        }
    }
    if(left_or_right == 'r' && hit == false){//if bullet is from right tank then x value is decremented
        moverRect.x -= 15;
        if(frame == 0){
            srcRect = {986,374,43,36};
            frame = 1;
        }

        else if(frame == 1){ 
            srcRect = {853,373,44,38};
            frame = 2; 
        }

        else if(frame == 2){ 
            srcRect = {809,376,38,31};
            frame = 3;
        }

        else if(frame == 3){ 
            srcRect = {765,381,31,23};
            frame = 4;
        }

        else if(frame == 4){ 
            srcRect = {721,385,23,15};
            frame = 5;
        }

        else if(frame == 5){ 
            srcRect = {677,387,19,11};
            frame = 6;
        }
    }
}