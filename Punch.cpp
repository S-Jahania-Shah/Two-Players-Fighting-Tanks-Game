#include "Punch.hpp"
#pragma once 
#include "game.hpp"
Game temp_obj_3;

Punch::Punch(int x, int y,char tank_pos){//parametrized constructor
    left_or_right = tank_pos;
    // src coorinates from assets.png file, they have been found using spritecow.com
    if(left_or_right == 'l'){
        srcRect = {614,485,107,38};
    }
    else if(left_or_right == 'r'){
        srcRect = {1626,64,192,60};
    }
    moverRect = {x, y, 100, 40};// at that certain x and y punch appear hojae ga
}

char Punch::get_tank_char()//returning which punch is it  either from left tank or right tank
{
    return left_or_right;
}

bool Punch::blast_it()
{
    return hit;
}

SDL_Rect Punch::getcoords(){
    return moverRect;//returning mover rect of tank 
}
// functionalities

void Punch::move(){
    if(left_or_right == 'l' && hit == false)//if punch is from left tank
    {
        moverRect.x += 25; //punch moves towards right tank
        if(frame == 0){// the initial state of the punch
            srcRect = {614,485,107,38};
            frame = 1; // the state changes to the next state
        }

        else if(frame == 1){ // the second state of the punch
            srcRect = {615,525,143,38};
            frame = 2; // the state changes to the next state
        }

        else if(frame == 2){ // the final state of the punch
            srcRect = {615,566,179,38};
            frame = 3;// the state is resetted and the process repeats
        }

        else if(frame == 3){ // the final state of the punch
            srcRect = {614,606,216,39};
            frame = 4;// the state is resetted and the process repeats
        }
        else if(frame == 4){// the initial state of the punch
            srcRect = {614,485,107,38};
            frame = 0; // the state changes to the initial state
        }
    }

    else if(left_or_right == 'r' && hit == false)// if punch is of right tank 
    {
        moverRect.x -= 25;//then it moves towards left tank
        if(frame == 0){// the initial state of the punch
            srcRect = {1626,64,192,60};
            frame = 1; // the state changes to the next state
        }

        else if(frame == 1){ // the second state of the punch
            srcRect = {1566,131,251,60};
            frame = 2; // the state changes to the next state
        }

        else if(frame == 2){ 
            srcRect = {1509,197,308,60};
            frame = 3;
        }

        else if(frame == 3){ 
            srcRect = {1450,263,367,61};
            frame = 4;
        }

        else if(frame == 4){ // the final state of the punch
            srcRect = {1626,64,192,60};
            frame = 0;// the state is resetted and the process repeats
        }
    }
}


void Punch::delete_Punch(){//dleete the punch and make the explosion animation as soon as collision happens
    if (hit == false)
    {
        temp_obj_3.play_collision_sound();// to play sound upon collision
        hit = true;// collision has taken place
        srcRect={694,77,26,19};
        frame = 6996;// just assigning random frame to start the new animations
    }
    else
    {//npow the state sof pucnhes will change
        if(frame == 6996){ 
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
            srcRect = {0,0,0,0};
        }
        //we changed the states of pucnhes based on different src rect values
    }
}