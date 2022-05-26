
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <fstream>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#pragma once 
#include <time.h>
#include <vector>
// #include "HUMania.hpp"
using namespace std;

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    // The music that will be played in game
    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    

public:


    
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
    void play_collision_sound();
};

