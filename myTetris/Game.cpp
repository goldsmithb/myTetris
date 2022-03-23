#include "Game.h"

Game::Game()
    : windowTitle("myTetris"), windowXPos(SDL_WINDOWPOS_CENTERED), 
      windowYPos(SDL_WINDOWPOS_CENTERED), winW(gWidth), winH(gHeight), 
      fullscreen(false), isRunning(false), window(nullptr), renderer(nullptr),
      currentPiece(nullptr), heldPiece(nullptr), gameField(nullptr)
{
    init(windowTitle, windowXPos, windowYPos, winW, winH, fullscreen);
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

        int x = 10;                                 // ERROR
        while (x-- > 0) {
            std::cout << "PRNGPRNGPRNG : " << prng(mt) << std::endl;
        }

        gameField = new GameField(renderer, lightBlue, GameObject::gUnit, width, height);

        // populate the queue
        for (int i = 0; i < 5; i++) {
            GamePiece* newPiece = new GamePiece(renderer, GameObject::gUnit, Piece(prng(mt)), GameObject::FIELD_WIDTH, gameField->accessPos());
            piecesQueue.push(newPiece);
        }

        // Make the first piece
        currentPiece = popPiece(); 

    } else {
        std::cout << "SDL Failed to initialize. Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
}

void Game::processKeyEvent(SDL_Event event) {
    bool rotationFlag = false;

    switch (event.key.keysym.sym) {
    case SDLK_UP:
        // Fall until collision detected
        while (detectCollision(*currentPiece, *gameField) == -1) {
            currentPiece->move(0, 1);
        }
        break;
    case SDLK_DOWN:
        currentPiece->move(0, 1);
        break;
    case SDLK_LEFT:
        if (detectBlockage(Left) == false)
            currentPiece->move(-1, 0);
        break;
    case SDLK_RIGHT:
        if (detectBlockage(Right) == false)
            currentPiece->move(1, 0);
        break;
    case SDLK_x:
    case SDLK_z:
        currentPiece->rotate(event);
        rotationFlag = true;
        break;
    case SDLK_SPACE:
        hold();
        break;
    default:
        break;
    }

    if (rotationFlag) {
        bumpRotation();
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

void Game::update() { 

    // update game variables
    gameField->update();
    currentPiece->update();

    // detect whether a block has landed
    int collision = detectCollision(*currentPiece, *gameField);
    switch (collision) {
    case 1 :
        // We collided with a block --> bumb the piece back
        //std::cout << "Debugging collisions:\n";         // ERROR
        //currentPiece->printGameObjectVector();          // ERROR
        //gameField->printGameObjectVector();             // ERROR
        currentPiece->move(0, -1);
    case 0:
        // landed on bottom row, no need to bump
        // absorb the piece into field
        gameField->absorb(*currentPiece);
        // delete currentPiece;
        // N.B. we don't call destructor because no heap allocation WITHIN the gamePiece struct occurs
        delete currentPiece;
        // choose new currentPiece
        currentPiece = popPiece();

    case -1 : // no collision
    default :
        break;
    }

}

void Game::render() {
    // clear render buffer & draw window base color
    //std::cout << "entered Game::render()\n";                // ERROR
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

bool Game::detectBlockage(enum Side side) {
    Position possible;
    int pieceVecSize = currentPiece->getHeight();
    int righttWallIndex = gameField->getWidth() - 1;
    std::vector<std::vector<char>> pieceVec = currentPiece->accessPixelVec();
    std::vector<std::vector<char>> gameFieldVec = gameField->accessPixelVec();

    switch (side) {
    case Left:
        possible = translateLocalToGlobal(currentPiece->accessPos(),
            gameField->accessPos());
        // Don't move if there is a fallen block to the left of any of the currentPiece blocks
        // for each block in pieceVec, check if there is a block in gameField to the left
        // or if we've hit the side of the gameField
        for (int y = 0; y < pieceVecSize; y++) {
            for (int x = 0; x < pieceVecSize; x++) {
                if (pieceVec[y][x]) {
                    if (((possible.x + x - 1) < 0) ||
                        gameFieldVec[possible.y + y][possible.x + x - 1] == 1) {
                        std::cout << "Blocked on the left!" << std::endl;
                        return true;
                    }
                }
            }
        }
        break;
    case Right:
        possible = translateLocalToGlobal(currentPiece->accessPos(),
            gameField->accessPos());
        // Don't move if there is a fallen block to the left of any of the currentPiece blocks
        // for each block in pieceVec, check if there is a block in gameField to the left
        for (int y = 0; y < pieceVecSize; y++) {
            for (int x = 0; x < pieceVecSize; x++) {
                if (pieceVec[y][x]) {
                    if (((possible.x + x + 1) > righttWallIndex) ||
                        gameFieldVec[possible.y + y][possible.x + x + 1] == 1) {
                        std::cout << "Blocked on the right!" << std::endl;
                        return true;
                    }
                }
            }
        }
        break;
    default:
        break;
    }

    return false;
}

void Game::bumpRotation() {
    bool OOB = true;
    int WH = currentPiece->getWidth();
    int fieldW = gameField->getWidth();
    Position lPiecePosition = translateLocalToGlobal(currentPiece->accessPos(), gameField->accessPos());
    std::vector<std::vector<char>> pieceVec = currentPiece->accessPixelVec();

    for (int y = 0; y < WH; y++) {
        for (int x = 0; x < WH; x++) {
            while (OOB) {
                // Check if we are out of bounds
                if (pieceVec[y][x]) {
                    //std::cout << "checking..." << std::endl; // ERROR
                    if ((x + lPiecePosition.x) < 0) {
                        currentPiece->move(1, 0);
                    }
                    else if ((x + lPiecePosition.x) >= fieldW) {
                        currentPiece->move(-1, 0);
                    }
                    else {
                        // no longer OOB
                        break;
                    }
                }
                // No block in this position
                break;
            }
        }
    }
}

GamePiece* Game::popPiece() {
    GamePiece* ret = piecesQueue.front();
    piecesQueue.pop();

    GamePiece* newPiece = new GamePiece(renderer, GameObject::gUnit, Piece(prng(mt)), GameObject::FIELD_WIDTH, gameField->accessPos());

    piecesQueue.push(newPiece);

    return ret;
}

// NOTICE: Abandoned lol but the code could come in handy later
Position Game::quickFall() {
    // approach: find the highest block in gameField that is in the 'shadow'
    // of the currentPiece (i.e. in the collumn underneath the piece);
    int pieceVecSize = currentPiece->getWidth();
    Position piecePos = translateLocalToGlobal(currentPiece->accessPos(), gameField->accessPos());
    Position returnVal = { 0,0 };
    std::vector<std::vector<char>> pieceVec = currentPiece->accessPixelVec();

    // from bottom-up, check the gameField for the highest block in the
    // 5-unit column underneath the current piece

    // determine shadow width
    int shadowX, shadowEnd;
    // set to furthest left
    shadowX = piecePos.x + pieceVecSize;
    // set to furthest right
    shadowEnd = piecePos.x;
    for (int x = 0; x < pieceVecSize; x++) {
        for (int y = 0; y < pieceVecSize; y++) {
            // if there is a block there and it is the furthest right yet, set as the start of the shadow
            if (pieceVec[y][x] != 0) {
                // must add piecePos.x because we need to translate to the 
                // gameField local orientation -- that's what the shadow is in
                if (piecePos.x + x < shadowX) {
                    shadowX = piecePos.x + x;
                }
                if (piecePos.x + x > shadowEnd) {
                    shadowEnd = piecePos.x + x;
                }
            }
        }
    }

    //std::cout << "shadow span: begin at " << shadowX << " -- " << shadowEnd << std::endl; // ERROR

    // check the gameField from bottom up to find the top block in the column
    int fieldVecW = gameField->getWidth();
    int fieldVecH = gameField->getHeight();
    int topY = fieldVecH + 1;               // Set as out of bounds value
    std::vector<std::vector<char>> gameFieldVec = gameField->accessPixelVec();

    for (int x = shadowX; x < shadowEnd; x++) {
        for (int y = (fieldVecH - 1); y >= 0; y--) {
            if (gameFieldVec[y][x] != 0 && y < topY) {
                topY = y;
            }
        }
    }

    std::cout << "topY detected as: " << topY << std::endl;     // ERROR

    return returnVal;

}

// handle the hold event:
// set current piece as heldPiece
// if there was already a heldPiece, set as currentPiece
// else, popPiece

void Game::hold() {
    GamePiece* temp = heldPiece;

    heldPiece = currentPiece;

    // reset heldPiece pos
    Position pos = currentPiece->accessPos();
    Position GFXY = gameField->accessPos();
    pos.x = GFXY.x;
    pos.y = GFXY.y;
    pos.x += gUnit * ((GameObject::FIELD_WIDTH - PIECE_WIDTH_HEIGHT) / 2);
    currentPiece->setPos(pos);

    if (temp) {
        currentPiece = temp;
    }
    else {
        currentPiece = popPiece();
    }
}


/*          FUNCTIONS           */

// TODO : allow things to land by moving in from the left/right
// TODO if returns true: move the piece up one unit, let the field absorb it :) yum
// returns: -1 if no collision
//          0 if collided with the field's floor
//          1 if collided with a block
int detectCollision(GameObject piece, GameObject field) {
    std::vector<std::vector<char>> pieceMatrix, fieldMatrix;
    pieceMatrix = piece.accessPixelVec(), fieldMatrix = field.accessPixelVec();
    int fieldHeight = field.getHeight();
    int fieldWidth = field.getWidth();
    int pieceVecSize = piece.getHeight();

    // store piece's pixel pos relative to field's local origin
    Position fieldGXY = field.accessPos();
    Position pieceLXY = piece.accessPos();
    // TODO : NOTE THAT THIS POS IS IN UNITS!

    pieceLXY = translateLocalToGlobal(pieceLXY, fieldGXY);

    // QUESTION  is this 4x nested for loop needed? So uggo
    // check for collisions
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            // For each landed block and the entire bottom row, check collision
            // cases: block on none-bottom row
            //        empty bottom row
            //        block on bottom row
            if (fieldMatrix[i][j] || i == (fieldHeight - 1)) {
                // Check if there is a collision with any block in the currentPiece
                for (int y = 0; y < pieceVecSize; y++) {
                    for (int x = 0; x < pieceVecSize; x++) {
                        // check if the localized coordinates match --> collision
                        if (pieceMatrix[y][x] && i == (pieceLXY.y + y) && j == (pieceLXY.x + x)) {
                            std::cout << "possible collision at:" << std::endl;
                            std::cout << "\tGlobal y: " << i << "\tx: " << j << "\n\tLocal y: " << (pieceLXY.y) << "\tLocal x: " << (pieceLXY.x) << std::endl;
                            // TODO : this fn might not be doing what I want exactly...
                            // did we collide, or just hit the bottom?
                            if (fieldMatrix[i][j] == 0) {
                                return 0;
                            }
                            else {
                                std::cout << "collision detected!!" << std::endl; // ERROR
                                return 1;
                            }

                        }
                    }
                }
            }
        }
    }

    // No collision detected
    return -1;
}