#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "GamePiece.h"


/*		GLOBAL VARIABLES		*/
const int gFPS = 60;
const int gFrameDelay = 1000 / gFPS;
const int gWidth = 300;
const int gHeight = 800;
const int gUnit = 50;
const Color gBackGroundColor = { 200, 162, 200 }; // TODO use this in init
const Position gOrigin = { 0, 0 };


/* Game class
 * 
 * 
 * 
 */
class Game {

public:
    Game();
    ~Game();

    // initialize the game window
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    // checks if the game is currently running
    bool running() { return isRunning; }

    // TODO : add these properties:
    // 
    // GameObject currentBlock;
    // std::vector<GameObject> blockQueue
    // GameObject field

private:
    bool isRunning;
    SDL_Window* window;

    // Global renderer
    SDL_Renderer* renderer;
};