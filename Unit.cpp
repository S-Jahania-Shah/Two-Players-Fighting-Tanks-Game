#include <iostream>
#include "Unit.hpp"
using namespace std;

void Unit::draw(){
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect); // creates object
    move(); // calling move function for animation

}
Unit::Unit(){};

Unit::Unit(SDL_Rect src_) { // default constructor which gets called barely
// made it to remove any error that may occur while the code runs
    srcRect = src_; // the position for the objects to fetch
    moverRect = {10, 20, 50, 50}; // coords of the moving rectangle
}


Unit::Unit(SDL_Rect src_, SDL_Rect mover_) { 
    srcRect = src_; // the position for the objects to fetch
    moverRect = mover_; // coords of the moving rectangle
}


void Unit::move(){} // empty move virtual function which would be overrided in the inherited classes. It would be defined there.