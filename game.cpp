#pragma once
#include "game.hpp"
#include "HUMania.hpp"
#include "life.hpp"
#include "drawing.hpp"
#include <SDL_mixer.h>
SDL_Renderer *Drawing::gRenderer = NULL;
SDL_Texture *Drawing::assets = NULL;
// implementing sound effects
Mix_Music *start_screen_music = NULL;
Mix_Music *back_grnd_music = NULL;

Mix_Chunk *crow_sound = NULL;
Mix_Chunk *button_sound = NULL;
Mix_Chunk *missile_sound = NULL;
Mix_Chunk *bullet_sound = NULL;
Mix_Chunk *punch_sound = NULL;
Mix_Chunk *explosion_sound = NULL;

bool Game::init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("HU Mania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			Drawing::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (Drawing::gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(Drawing::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	// Loading success flag
	bool success = true;
	gTexture = loadTexture("screen 0.png");
	Drawing::assets = loadTexture("assets.png");
	// gTexture = loadTexture("hu.png");
	if (Drawing::assets == NULL || gTexture == NULL)
	{
		printf("Unable to run due to error: %s\n", SDL_GetError());
		success = false;
	}
	back_grnd_music = Mix_LoadMUS("background_music.wav");
	if (back_grnd_music == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	start_screen_music = Mix_LoadMUS("start_end_music.wav");
	if (start_screen_music == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	button_sound = Mix_LoadWAV("button_press.wav");
	if (button_sound == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	missile_sound = Mix_LoadWAV("missile_sound.wav");
	if (missile_sound == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	bullet_sound = Mix_LoadWAV("bullet_sound.wav");
	if (bullet_sound == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	punch_sound = Mix_LoadWAV("punch_sound.wav");
	if (punch_sound == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	explosion_sound = Mix_LoadWAV("explosion_sound.wav");
	if (explosion_sound == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	crow_sound = Mix_LoadWAV("crow_sound.wav");
	if (explosion_sound == NULL)
	{
		printf("Failed to load the background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

void Game::close()
{
	// Free loaded images
	SDL_DestroyTexture(Drawing::assets);
	Drawing::assets = NULL;
	SDL_DestroyTexture(gTexture);

	// Destroy window
	SDL_DestroyRenderer(Drawing::gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	Drawing::gRenderer = NULL;

	start_screen_music = NULL;
	back_grnd_music = NULL;
	button_sound = NULL;
	missile_sound = NULL;
	bullet_sound = NULL;
	punch_sound = NULL;
	explosion_sound = NULL;
	crow_sound = NULL;
	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

SDL_Texture *Game::loadTexture(std::string path)
{
	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Drawing::gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Game::play_collision_sound()
{
	Mix_PlayChannel(-1, explosion_sound, 0);
	cout << "playing explosion sound" << endl;
}

void Game::run()
{
	bool quit = false;
	SDL_Event e;
	static int screen = 0;
	int score1 = 0;
	int score2 = 0;
	int hit_left_tank = 0;
	int hit_right_tank = 0;

	int heart_r = 0;
	int heart_l = 0;
	HUMania humania;

	humania.initialize();
	// playing the music only if game is running

	Mix_PlayMusic(start_screen_music, -1);
	while (!quit)
	{

		// Handle events on queue
		
		while (SDL_PollEvent(&e) != 0)
		{
			int xMouse, yMouse;
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				Mix_PlayChannel(-1, button_sound, 0);
				quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
			// this is a good location to add pigeon in linked list.
			{
				Mix_PlayChannel(-1, button_sound, 0); // playing button sounds
				int xMouse, yMouse;
				std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				cout<<xMouse<<", "<<yMouse<<endl;
				if ((xMouse >= 448 && xMouse <= 578 && yMouse >= 322 && yMouse <= 367) || (xMouse >= 436 && xMouse <= 447 && yMouse >= 331 && yMouse <= 359) || (xMouse >= 575 && xMouse <= 591 && yMouse >= 330 && yMouse <= 361))
				{
					// Screen = 1;
					Mix_PlayChannel(-1, button_sound, 0); // playing button sounds
					cout << "screen changed." << endl;
					gTexture = loadTexture("hu.jpeg");
					screen = 1;
					// ending the start end/music and playing the game music

					if (Mix_PlayingMusic() == 1)
					{
						Mix_PauseMusic();
						Mix_PlayMusic(back_grnd_music, -1);
						Mix_PlayChannel(-1, crow_sound, 0);
					}
				}

				if (screen == 1){
					if (((xMouse >= 460 && xMouse <= 540 && yMouse >= 8 && yMouse <= 57) || (xMouse >= 444 && xMouse <= 465 && yMouse >= 13 && yMouse <= 52) || (xMouse >= 541 && xMouse <= 555 && yMouse >= 13 && yMouse <= 52))){
						gTexture = loadTexture("screen 0.png");
						screen = 0;
					}
				}
				if ((xMouse >= 435 && xMouse <= 600 && yMouse >= 405 && yMouse <= 451) || (xMouse >= 426 && xMouse <= 436 && yMouse >= 409 && yMouse <= 448))
				{
					// Screen = 1;
					Mix_PlayChannel(-1, button_sound, 0); // playing button sounds
					cout << "screen changed." << endl;
					gTexture = loadTexture("screen 1.png");
					screen = 2;

					// ending the game music and playing the start end/music

					if (Mix_PlayingMusic() == 1)
					{
						Mix_PauseMusic();
						Mix_PlayMusic(start_screen_music, -1);
					}
				}
				if ((xMouse >= 461 && xMouse <= 562 && yMouse >= 478 && yMouse <= 538) || (xMouse >= 446 && xMouse <= 462 && yMouse >= 486 && yMouse <= 528) || (xMouse >= 564 && xMouse <= 581 && yMouse >= 482 && yMouse <= 531))
				{
					Mix_PlayChannel(-1, button_sound, 0); // playing button sounds
					cout << "screen changed." << endl;
					quit = true;
				}
				if (screen == 2)
				{

					if ((xMouse >= 29 && xMouse <= 102 && yMouse >= 28 && yMouse <= 69) || (xMouse >= 14 && xMouse <= 29 && yMouse >= 34 && yMouse <= 63) || (xMouse >= 104 && xMouse <= 115 && yMouse >= 34 && yMouse <= 64))
					{
						Mix_PlayChannel(-1, button_sound, 0); // playing button sounds
						gTexture = loadTexture("screen 0.png");
						screen = 0;
						// ending the game music and playing the start end/music

						if (Mix_PlayingMusic() == 1)
						{
							Mix_PauseMusic();
							Mix_PlayMusic(start_screen_music, -1);
						}
					}
				}
				if (screen == 3){
					if ((xMouse >= 37 && xMouse <= 152 && yMouse >= 25 && yMouse <= 93) || (xMouse >= 13 && xMouse <= 37 && yMouse >= 22 && yMouse <= 24) || (xMouse >= 150 && xMouse <= 172 && yMouse >= 22 && yMouse <= 24)){
						
						gTexture = loadTexture("screen 0.png");
						screen = 0;
						
						score1 = 0;
						score2 = 0;
						hit_left_tank = 0;
						hit_right_tank = 0;

						heart_r = 0;
						heart_l = 0;
						
						humania.initialize();
					}
				}
			}


			// for punches
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
			{ // creates left punch from tank 1
				Mix_PlayChannel(-1, punch_sound, 0);
				int xMouse, yMouse;
				// std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				SDL_GetMouseState(&xMouse, &yMouse);

				if (screen == 1)
				{
					SDL_Rect a = humania.get_tank_coords(0);
					cout << "Tank 1 coords: " << a.x << " " << a.y << endl;
					int x_coord = a.x + a.w;
					int y_coord = a.y + a.h / 4;
					humania.createPunch(x_coord, y_coord, 'l');
					Mix_PlayChannel( -1, explosion_sound, 0 );

					score1 += 1;
					score2 -= 1;		 // 1 ka score brhy ga tuh 2 ka kam hoga na
					hit_right_tank += 1; // tank right ko akr laga hai
				}
			}

			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)

			{ // creates right punch from tank 2
				Mix_PlayChannel(-1, punch_sound, 0);

				int xMouse, yMouse;
				// std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				// int xMouse, yMouse;
				if (screen == 1)
				{
					cout << "Right Punch should come out" << endl;
					// humania.createPunch(215, 335);
					SDL_Rect a = humania.get_tank_coords(1);
					cout << "Tank 2 coords: " << a.x << " " << a.y << endl;
					int x_coord = a.x - 95;
					int y_coord = a.y + a.h / 2 - 15;
					humania.createPunch(x_coord, y_coord, 'r');
					score2 += 1;
					score1 - +1; // punch marny sy score aik brhta, jisy lagy uska kam hojata
					hit_left_tank += 1;
				}
			}

			// for missiles
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w)
			{ // creates left punch from tank 1
				Mix_PlayChannel(-1, missile_sound, 0);

				int xMouse, yMouse;
				// std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (screen == 1)
				{
					cout << "Left missile should come out" << endl;
					SDL_Rect a = humania.get_tank_coords(0);
					cout << "Tank 1 coords: " << a.x << " " << a.y << endl;
					int x_coord = a.x + a.w;
					int y_coord = a.y + a.h / 16;
					humania.createMissile(x_coord, y_coord, 'l');
					score1 += 2;
					score2 -= 2; // missile marny waly ka score increase by 2 and lagny waly ka decrease by -2
					hit_right_tank += 1;
				}
			}

			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m)
			{ // creates right punch from tank 2
				Mix_PlayChannel(-1, missile_sound, 0);

				int xMouse, yMouse;
				// std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				// int xMouse, yMouse;
				if (screen == 1)
				{
					cout << "Right Punch should come out" << endl;
					// humania.createPunch(215, 335);
					SDL_Rect a = humania.get_tank_coords(1);
					cout << "Tank 2 coords: " << a.x << " " << a.y << endl;
					int x_coord = a.x - 95;
					int y_coord = a.y + a.h / 2 - 15;
					humania.createMissile(x_coord, y_coord, 'r');
					score2 += 1;
					score1 -= 1;
					hit_left_tank += 1;
				}
			}

			// for bullets
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e)
			{ // creates left punch from tank 1
				Mix_PlayChannel(-1, bullet_sound, 0);

				int xMouse, yMouse;
				// std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (screen == 1)
				{
					cout << "Left bullets should come out" << endl;
					SDL_Rect a = humania.get_tank_coords(0);
					cout << "Tank 1 coords: " << a.x << " " << a.y << endl;
					int x_coord = a.x + a.w;
					int y_coord = a.y + a.h / 16;
					humania.createBullets(x_coord, y_coord, 'l');
					score1 += 3;
					score2 -= 3; // marain tuh +3 lagy tuh -3
					hit_right_tank += 1;
				}
			}

			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b)
			{ // creates right punch from tank 2
				Mix_PlayChannel(-1, bullet_sound, 0);

				int xMouse, yMouse;
				// std::cout << SDL_GetMouseState(&xMouse, &yMouse) << std::endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				// int xMouse, yMouse;
				if (screen == 1)
				{
					cout << "Right bullets should come out" << endl;
					// humania.createPunch(215, 335);
					SDL_Rect a = humania.get_tank_coords(1);
					cout << "Tank 2 coords: " << a.x << " " << a.y << endl;
					int x_coord = a.x - 95;
					int y_coord = a.y + a.h / 2 - 15;
					humania.createBullets(x_coord, y_coord, 'r');
					score2 += 3;
					score1 -= 3;
					hit_left_tank += 1;
				}
			}

			else if (e.type == SDL_KEYDOWN)
				if (screen == 1)
				{
					//if (tank5.x + tank5.w < right_tank1.x)
					humania.moveobjects(Drawing::gRenderer, Drawing::assets, e.key.keysym.sym);
				}
			
		}

		SDL_RenderClear(Drawing::gRenderer);					  // removes everything from renderer
		SDL_RenderCopy(Drawing::gRenderer, gTexture, NULL, NULL); // Draws background to renderer
		// collison of missile from left tank to the right tank
		SDL_Rect right_tank1 = humania.get_tank_coords(1);	 // this gives the coordinates of tank 1
		humania.detect_collision_missiles(right_tank1, 'l'); // if right tank ky and left missile ky x coordinate matches
		// collision of fire from left tank to right tank
		SDL_Rect right_tank2 = humania.get_tank_coords(1); // this gives the coordinates of tank 1
		humania.detect_collision_fire(right_tank2, 'l');   // if right tank ky and left missile ky x coordinate matches
		// collision of punches from left tank to right tank
		SDL_Rect right_tank3 = humania.get_tank_coords(1);	// this gives the coordinates of tank 1
		humania.detect_collision_punches(right_tank3, 'l'); // if right tank ky and left missile ky x coordinate matches
		// collision of TNTs
		SDL_Rect tank4 = humania.get_tank_coords(1);	   // this gives the coordinates of tank 1
		bool check1 = humania.detect_collision_TNT(tank4); // if right tank ky and left missile ky x coordinate matches

		SDL_Rect tank5 = humania.get_tank_coords(0);	   // this gives the coordinates of tank 1
		bool check0 = humania.detect_collision_TNT(tank5); // if right tank ky and left missile ky x coordinate matches

		
		SDL_Rect tank_tnt2_right = humania.get_tank_coords(1);	   // this gives the coordinates of tank 1
		bool check_tnt2_right = humania.detect_collision_TNT2(tank_tnt2_right); // if right tank ky and left missile ky x coordinate matches

		SDL_Rect tank_tnt2_left = humania.get_tank_coords(0);	   // this gives the coordinates of tank 1
		bool check_tnt2_left = humania.detect_collision_TNT2(tank_tnt2_left); // if right tank ky and left missile ky x coordinate matches

		// collison of missile from right tank to the left tank
		SDL_Rect left_tank1 = humania.get_tank_coords(0);	// this gives the coordinates of tank 1
		humania.detect_collision_missiles(left_tank1, 'r'); // if right tank ky and left missile ky x coordinate matches
		// collision of fire from right tank to left tank
		SDL_Rect left_tank2 = humania.get_tank_coords(0); // this gives the coordinates of tank 1
		humania.detect_collision_fire(left_tank2, 'r');	  // if right tank ky and left missile ky x coordinate matches
		// collision of punches from right tank to left tank
		SDL_Rect left_tank3 = humania.get_tank_coords(0);  // this gives the coordinates of tank 1
		humania.detect_collision_punches(left_tank3, 'r'); // if right tank ky and left missile ky x coordinate matches
		// collision of TNTs
		SDL_Rect tank44 = humania.get_tank_coords(0);				 // this gives the coordinates of tank 1
		bool check_0 = humania.detect_collision_firecracker(tank44); // if right tank ky and left missile ky x coordinate matches

		SDL_Rect tank45 = humania.get_tank_coords(1);				 // this gives the coordinates of tank 1
		bool check_1 = humania.detect_collision_firecracker(tank45); // if right tank ky and left missile ky x coordinate matches
		//***********************draw the objects here********************
		// if (screen == 1){
		// humania.createObject(xMouse, yMouse);

		// }
		if (check1 == true || check_1 == true || check_tnt2_right==true)
			hit_right_tank += 1;

		else if (check0 == true || check_0 == true || check_tnt2_left==true)
			hit_left_tank += 1;

		if (hit_left_tank == 4)
		{
			humania.detect_heart('l', 0); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_left_tank == 8)
		{

			humania.detect_heart('l', 1); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_left_tank == 16)
		{
			humania.detect_heart('l', 2); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_left_tank == 24)
		{
			humania.detect_heart('l', 3); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_left_tank > 24)
		{
			humania.detect_heart('l', 4); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}

		if (hit_right_tank == 4)
		{
			humania.detect_heart('r', 0); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_right_tank == 8)
		{
			humania.detect_heart('r', 1); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_right_tank == 16)
		{
			humania.detect_heart('r', 2); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_right_tank == 24)
		{
			humania.detect_heart('r', 3); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}
		else if (hit_right_tank > 24)
		{
			humania.detect_heart('r', 4); // matlab rightb waly ka aik heart kaam hoga ab //1 indicates ky aik heart kam krna hai
		}

		// now defiing the hit conditions for the left tank:

		if (hit_right_tank > 24)
		{
			gTexture = loadTexture("endgame2.PNG"); // right tank ki all helath gone left tank wins.
			screen = 3;
			humania.clear_object();

		}
		else if (hit_left_tank > 24)
		{
			gTexture = loadTexture("endgame1.PNG");
			screen = 3;
			humania.clear_object();

		}
		if (screen == 1)//this is for randomly making the objects fall from sky
		{
			int a = rand() % 60;
			if (a == 1)
			{
				int b = rand() % 1000 + 1;
				humania.createObject(b, 0);
			}
			humania.drawObjects();
		}
		// humania.update_screen();
		//****************************************************************
		SDL_RenderPresent(Drawing::gRenderer); // displays the updated renderer

		SDL_Delay(100); // causes sdl engine to delay for specified miliseconds
	}
}
