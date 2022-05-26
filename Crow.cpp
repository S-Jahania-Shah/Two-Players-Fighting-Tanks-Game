#include "Crow.hpp"
// pigeon implementation will go here.
// constructors
#pragma once 

Crow::Crow(){}

Crow::Crow(int x, int y){
    // src coorinates from assets.png file, they have been found using spritecow.com
    srcRect = {538, 1725, 136, 58};
    moverRect = {x, y, 50, 50};
}

// functionalities

void Crow::draw(){//to draw the crow
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect); // creates object

    move(); // calling move function for animation
}

void Crow::move(){
    
    // the crow accelerares on the right x-axis
    moverRect.x -= 10;

    if(moverRect.x < 0){ // if the object reaches the end of the right screen, the x pixels are set to -30 to have a continuous motion
        moverRect.x = 1001;
    }

    if(frame == 0){// the initial state of the crow
        srcRect = {365,1725,137,79};
        frame = 1; // the state changes to the next state
    }

    else if(frame == 1){ // the second state of the crow
        srcRect = {192,1725,137,58};
        frame = 2; // the state changes to the next state
    }

    else if(frame == 2){ 
        srcRect = {19,1701,137,76};
        frame = 3;
    }

    else if(frame == 3){
        srcRect = {538, 1725, 136, 58};
        frame = 0; // the state cthen repeats
    }
}