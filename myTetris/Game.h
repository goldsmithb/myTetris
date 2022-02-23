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

    // initialize SDL, the window, the renderer
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void processKeyEvent(SDL_Event event);
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
    const char* windowTitle;        // Title for the window
    int windowXPos;                 // window X Pos
    int windowYPos;                 // window Y pos
    int winW;                       // window width
    int winH;                       // window height
    bool fullscreen;                // fullscreen window boolean

    bool isRunning;                 // game loop boolean

    SDL_Window* window;

    SDL_Renderer* renderer;         // Global renderer

    GamePiece* currentPiece;         // Current Piece

    GamePiece** piecesQueue;         // Pieces Queue

    GameObject* gameField;           // Game Field
};