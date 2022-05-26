#include <SDL.h>
#include "Tank.hpp"
#include "firecracker.hpp"
#include "Punch.hpp"
#include "Missile.hpp"
#include "Crow.hpp"
#include "Bullets.hpp"
#include "TNT.hpp"
#include "TNT2.hpp"
#include "life.hpp"
#include "Weapons.hpp"
#include <vector>
#include <list>
#pragma once
using namespace std;

class HUMania
{
    //vector of all classes are being created
    vector<Tank *> tanks; 
    vector<firecracker *> firecrack;
    vector<Punch *> punches;
    vector<Missile *> missiles;
    vector<Bullets *> bullets;
    // vector<Weapons *> weapons;
    vector<TNT *> TNTs;
    vector<TNT2 *> TNT2s;
    vector<life *> heart;
    vector<Crow *> crows;

public:
    //functionalities of each tank is explained in cpp file.
    void clear_object();
    void drawObjects();
    void createObject(int, int);
    void createPunch(int, int, char);
    void createMissile(int, int, char);
    void createBullets(int, int, char);
    void update(SDL_Renderer *gRenderer, SDL_Texture *assets);
    void moveobjects(SDL_Renderer *gRenderer, SDL_Texture *assets, SDL_Keycode key);
    void initialize();
    SDL_Rect get_tank_coords(int tank_no);
    void detect_collision_missiles(SDL_Rect, char);
    bool detect_collision_TNT(SDL_Rect);
    bool detect_collision_TNT2(SDL_Rect);
    bool detect_collision_firecracker(SDL_Rect);
    void detect_collision_punches(SDL_Rect, char);
    void detect_collision_fire(SDL_Rect, char);
    void detect_heart(char, int);
    SDL_Rect get_missile_coords(int tank_no);

    ~HUMania(); // destroyer
};