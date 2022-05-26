#include "Missile.hpp"
#include "game.hpp"
// Missile implementation will go here.
// constructors
#pragma once 
Game temp_obj_2;

Missile::Missile(int x, int y,char tank_pos){//paramterized constructor
    left_or_right = tank_pos;
    // src coorinates from assets.png file, they have been found using spritecow.com
    if(left_or_right == 'l'){
        srcRect = {1618,373,49,17};
    }
    else if(left_or_right == 'r'){
        srcRect = {1421,373,48,17};
    }
    moverRect = {x, y, 100, 40};
}

SDL_Rect Missile::getcoords(){//return the moverrect
    return moverRect;
}
// functionalities

char Missile::get_tank_char()
{
    return left_or_right;//tells whihc tank has created the missile
}

bool Missile::blast_it()
{
    return hit;
}

void Missile::delete_missile(){//whn collsion takes place change the src rect of missile into explosion src rect
    if (hit == false){
        temp_obj_2.play_collision_sound();//play sound upon collision
        hit = true;
        srcRect={898,57,57,54};
        frame = 0;
    }
    else
    {//the states of explosion will be changing below:
        if(frame == 0){ 
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
        else if(frame == 14){//now the explosion effect also ends.
            srcRect = {0,0,0,0};
        }
    }
}


void Missile::move(){

    if(left_or_right == 'l' && hit == false){
        moverRect.x += 15;
        if(frame == 0){// the initial state of the punch
            srcRect = {1618,373,49,17};
            frame = 1; // the state changes to the next state
        }

        else if(frame == 1){ // the second state of the punch
            srcRect = {1605,405,62,22};
            frame = 2; // the state changes to the next state
        }

        else if(frame == 2){ // the final state of the punch
            srcRect = {1577,435,92,40};
            frame = 3;// the state is resetted and the process repeats
        }

        else if(frame == 3){ // the final state of the punch
            srcRect = {1573,488,97,21};
            frame = 4;// the state is resetted and the process repeats
        }
        else if(frame == 4){ // the final state of the punch
            srcRect = {1570,539,101,21};
            frame = 5;// the state is resetted and the process repeats
        }
        else if(frame == 5){ // the final state of the punch
            srcRect = {1564,589,109,18};
            frame = 6;// the state is resetted and the process repeats
        }
        
    }

    if(left_or_right == 'r' && hit == false){
        moverRect.x -= 15;
        if(frame == 0){// the initial state of the punch
            srcRect = {1421,373,48,17};
            frame = 1; // the state changes to the next state
        }

        else if(frame == 1){ // the second state of the punch
            srcRect = {1421,405,62,22};
            frame = 2; // the state changes to the next state
        }

        else if(frame == 2){ // the final state of the punch
            srcRect = {1419,435,92,40};
            frame = 3;// the state is resetted and the process repeats
        }

        else if(frame == 3){ // the final state of the punch
            srcRect = {1418,488,97,21};
            frame = 4;// the state is resetted and the process repeats
        }

        else if(frame == 4){ // the final state of the punch
            srcRect = {1417,540,101,20};
            frame = 5;// the state is resetted and the process repeats
        }

        else if(frame == 5){ // the final state of the punch
            srcRect = {1416,590,108,17};
            frame = 6;// the state is resetted and the process repeats
        }

    }
}