#include "Game.h"


Game::Game()
    : windowTitle("myTetris"), windowXPos(SDL_WINDOWPOS_CENTERED), 
      windowYPos(SDL_WINDOWPOS_CENTERED), winW(gWidth), winH(gHeight), 
      fullscreen(false), isRunning(false), window(nullptr), renderer(nullptr),
      currentPiece(nullptr), piecesQueue(nullptr), gameField(nullptr)
{
    init(windowTitle, windowXPos, windowYPos, winW, winH, fullscreen);
}

Game::~Game() {

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen == true) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized..." << std::endl;

        // create window
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        // create renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer created!" << std::endl;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff); // TODO make background color
        }

        isRunning = true;

        // Load game 
        // Load all the gameObjects!
        // TODO : pieces queue

        gameField = new GameField(renderer, lightBlue, gUnit, width, height);

        // Make the first piece
        currentPiece = new GamePiece(renderer, gUnit, Piece::I, FIELD_WIDTH, gameField->accessPos());
        
    } else {
        std::cout << "SDL Failed to initialize. Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
}

// TODO document
// Process key press event and update current surface respectively
void Game::processKeyEvent(SDL_Event event) {

    switch (event.key.keysym.sym) {
    case SDLK_UP:
        currentPiece->move(0, -1);
        break;
    case SDLK_DOWN:
        currentPiece->move(0, 1);
        break;
    case SDLK_LEFT:
        currentPiece->move(-1, 0);
        break;
    case SDLK_RIGHT:
        currentPiece->move(1, 0);
        break;
    case SDLK_x:
    case SDLK_z:
        currentPiece->rotate(event);
        break;
    default:
        break;
    }
}

// TODO document
// Process io events
// Right now, just quit and key events
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        processKeyEvent(event);
    default:
        break;
    }
}

// todo if returns true: move the piece up one unit, let the field absorb it :) yum
// returns: -1 if no collision
//          0 if collided with the field's floor
//          1 if collided with a block
int detectCollision(GameObject piece, GameObject field) {
    std::vector<std::vector<char>> pieceMatrix, fieldMatrix;
    pieceMatrix = piece.accessPixelVec(), fieldMatrix = field.accessPixelVec();
    int fieldHeight = field.getHeight();
    int fieldWidth = field.getWidth();

    // store piece's pixel pos relative to field's local origin
    Position fieldGXY = { field.accessPos().x, field.accessPos().y };
    Position pieceXY = { piece.accessPos().x, piece.accessPos().y };
    pieceXY.x -= fieldGXY.x;
    pieceXY.y -= fieldGXY.y;
    // now convert to block coordinates
    pieceXY.x /= gUnit;
    pieceXY.y /= gUnit;

    // QUESTION  is this 4x nested for loop needed? So uggo
    // TODO check from top to bottom
    // check for collisions
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            if (fieldMatrix[i][j] != 0 || 
                i == (fieldHeight - 1))    // always land on bottom row
            {
                // check for collision
                for (int y = 0; y < 5; y++) {
                    for (int x = 0; x < 5; x++) {
                        if (pieceMatrix[y][x] != 0) {
                            if (i == (pieceXY.y + y) && 
                                j == (pieceXY.x + x)) 
                            {
                                // did we collide, or just hit the bottom?
                                if (fieldMatrix[i][j] == 0) {
                                    return 0;
                                } else {
                                    std::cout << "collision detected!!" << std::endl; // ERROR
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return -1;
}

void Game::update() { 

    // update game variables

    currentPiece->update();

    // detect whether a block has landed
    

}

void Game::render() {
    // clear render buffer & draw window base color
    SDL_SetRenderDrawColor(renderer, 235, 233, 178, 0xff); // TODO set as a bg color
    SDL_RenderClear(renderer);


    // Render Game Field space

    gameField->render();

    currentPiece->render();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}