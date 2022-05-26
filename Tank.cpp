#include "Tank.hpp"
#pragma once
// Tank implementation will go here.

void Tank::move(SDL_Keycode key, int tank_no)
{   
    if (key == SDLK_d && tank_no == 0)//if d key is pressed it means tank no is 0 that is its left tankk.
    {
        if (frame == 0)
        {                                         
            SDL_Rect values = {47, 477, 125, 93}; // sprite cow values of tank position 0
            srcRect = values;                     // update the srcRect
            frame = 1;                           
        }
        else if (frame == 1)
        {
            SDL_Rect values = {174, 476, 125, 94}; // sprite cow values of tank position 1
            srcRect = values;                     //  update the srcRect
            frame = 2;
        }
        else if (frame == 2)
        {
            SDL_Rect values = {301, 476, 125, 94};// sprite cow values of left tank position 2
            srcRect = values;                     //  update the srcRect
            frame = 3;
        }

        else if (frame == 3)
        {
            SDL_Rect values = {428, 476, 125, 94}; // sprite cow values of left tank position 3
            srcRect = values;                     //  update the srcRect
            frame = 4;
        }

        else if (frame == 4)
        {
            SDL_Rect values = {47, 477, 125, 93}; // sprite cow values of left tank position 5
            srcRect = values;                     //  update the srcRect
            frame = 0;//sets frame back to 0 to have smooth flow of tank moving 
        }

        if (moverRect.x >= 800)
        { // for tanks to stay on screen
            moverRect.x -= 5;
           
        }
        moverRect.x += 5; //move tank to right by 5 units
    }
    if (key == SDLK_a && tank_no == 0)// if key a is pressed then tank left moves towards left
    {
        if (frame == 0)
        {                                          
            SDL_Rect values = {428, 476, 125, 94}; // sprite cow values of left tank position 0
            srcRect = values;                     //  update the srcRect
            frame = 1;                             
        }
        else if (frame == 1)
        {
            SDL_Rect values = {301, 476, 125, 94}; // sprite cow values of left tank position 1
            srcRect = values;                     //  update the srcRect
            frame = 2;
        }
        else if (frame == 2)
        {
            SDL_Rect values = {174, 476, 125, 94}; // sprite cow values of left tank position 2
            srcRect = values;                     //  update the srcRect
            frame = 3;
        }

        else if (frame == 3)
        {
            SDL_Rect values = {47, 477, 125, 93}; // third image of the left tank moving twoards left
            srcRect = values;                     // updating values
            frame = 4;
        }

        else if (frame == 4)
        {
            SDL_Rect values = {428, 476, 125, 94}; // sprite cow values of left tank position 4
            srcRect = values;                     //  update the srcRect
            frame = 0;
        }

        if (moverRect.x < 0)
        { // for tanks to stay on screen
            moverRect.x += 5;
        }
        moverRect.x -= 5; // to move the tank in the right direction
    }

    if (key == SDLK_LEFT && tank_no == 1)//pressing left arrow key makes right tank move towards right
    {
        if (frame == 0)
        {                                           
            SDL_Rect values = {1886, 543, 257, 161}; // sprite cow values for right tank
            srcRect = values;                       
            frame = 1;                             
        }
        else if (frame == 1)
        {
            SDL_Rect values = {1886, 737, 257, 161}; // sprite cow values for right tank
            srcRect = values;                        // updating values
            frame = 2;
        }
        else if (frame == 2)
        {
            SDL_Rect values = {1886, 931, 257, 161}; // sprite cow values for right tank
            srcRect = values;                        // updating values
            frame = 3;
        }

        else if (frame == 3)
        {
            SDL_Rect values = {1886, 1126, 257, 161}; // // sprite cow values for right tank
            srcRect = values;                         // updating values
            frame = 4;
        }

        else if (frame == 4)
        {
            SDL_Rect values = {1886, 543, 257, 161}; // sprite cow values for right tank
            srcRect = values;                        // updating values
            frame = 0;
        }

        if (moverRect.x < 0)
        { // for tanks to stay on screen
            moverRect.x += 5;
        }

        moverRect.x -= 5; // to move the right tank in the left direction
    }

    if (key == SDLK_RIGHT && tank_no == 1)//pressing right key to move tank right to right side of screen.
    {
        if (frame == 0)
        {                                            
            SDL_Rect values = {1886, 543, 257, 161}; // sprite cow values
            srcRect = values;                       
            frame = 1;                               
        }
        else if (frame == 1)
        {
            SDL_Rect values = {1886, 1126, 257, 161}; 
            srcRect = values;                         // updating values
            frame = 2;
        }
        else if (frame == 2)
        {
            SDL_Rect values = {1886, 931, 257, 161}; 
            srcRect = values;                        // updating values
            frame = 3;
        }

        else if (frame == 3)
        {
            SDL_Rect values = {1886, 737, 257, 161};
            srcRect = values;                        // updating values of src rect for right tank moving towards right
            frame = 4;
        }

        else if (frame == 4)
        {
            SDL_Rect values = {1886, 543, 257, 161}; 
            srcRect = values;                        // updating values
            frame = 0;
        }

        if (moverRect.x + moverRect.w >= 1000)
        { // for tanks to stay on screen
            moverRect.x -= 5;
        }

        moverRect.x += 5; //  incrementing moverrect.x 
    }
}

SDL_Rect Tank::getcoords()//return mover rect of tank
{
    return moverRect;
}

Tank::Tank() : Unit()
{
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {27, 457, 125, 93};
    moverRect = {30, 40, 200, 120};
}
Tank::Tank(int x, int y) : Unit() // calling default unit deafult constructor as well.
{
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {27, 457, 125, 93};
    moverRect = {x, y, 200, 120};
    frame = 1;//setting initial frame to 1
}

Tank::Tank(int tank_no, SDL_Rect srcRect1, int x, int y)
{
    srcRect = srcRect1;
    if (tank_no == 0)
        moverRect = {x, y, 250, 200};//size of both tanks are slightly different
    else if (tank_no == 1)
        moverRect = {x, y, 300, 200};
    frame = 1;
}