#include "GameField.h"

GameField::GameField(SDL_Renderer* ren, Color c, int unitSize, int winW, int winH)
	: GameObject(ren, FIELD_WIDTH, FIELD_HEIGHT)
{
    bgColor = c;
    color = { 0xd3, 0xd3, 0xd3 };

    // calculate position by first converting the window dimensions from pixels to units,
    // performing the calculation, then converting back to pixels
    pos.x = GameObject::gUnit* std::abs(((winW / GameObject::gUnit) - FIELD_WIDTH) / 2);
    pos.y = GameObject::gUnit * std::abs(((winH / GameObject::gUnit) - FIELD_HEIGHT) / 2);
    fieldRect.x = pos.x;
    fieldRect.y = pos.y;
    fieldRect.w = FIELD_WIDTH * GameObject::gUnit;
    fieldRect.h = FIELD_HEIGHT * GameObject::gUnit;

    std::cout << " fieldMatrix rows : " << pixelVec.size() << std::endl;
    std::cout << " fieldMatrix collumns : " << pixelVec.at(0).size() << std::endl;
}

void GameField::render() {
    // Draw area of game field
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 0xff);

    SDL_RenderFillRect(renderer, &fieldRect);

    // render fallen blocks
    GameObject::render();
}

// ATM, basically checks for line clears. This should likely be put in a new fn in 
// case more things are added to update() later
void GameField::update() {
    //std::cout << "Entered GameField::update()\n";               // ERROR

    for (int y = 0; y < this->height; y++) {
        int count = 0;
        for (int x = 0; x < this->width; x++) {
            if (pixelVec[y][x]) {
                count++;
            }
        }
        // if line cleared, delete row and shift everything down
        if (count == this->width) {
            pixelVec.erase(pixelVec.begin() + y);
            pixelVec.insert(pixelVec.begin(), std::vector<char>(this->width, 0));
        }
    }
    //std::cout << "Exited GameField::update()\n";               // ERROR
}


void GameField::absorb(GameObject piece) {
    // TODO : RN the bug is here (aborts when landing I block on empty bottom row on far left) and also there is a bug detecting right wall!
    //std::cout << "Entered GameField::absorb()\n";               // ERROR

    std::vector<std::vector<char>> pieceVec = piece.accessPixelVec();
    Position pieceXY = translateLocalToGlobal(piece.accessPos(), this->pos);

    // iterate through the piece pixelVec
    for (int y = 0; y < piece.getHeight(); y++) {
        for (int x = 0; x < piece.getWidth(); x++) {
            // record a value where needed
            if (pieceVec[y][x]) {
                std::cout << "copying a block into the field at: [" << y<<"]["<<x<<"]" << std::endl; // 

                std::cout << "                             into: [" << (pieceXY.y + y) << "][" << (pieceXY.x + x) << "]" << std::endl; // ERROR
                this->pixelVec[pieceXY.y + y][pieceXY.x + x] = 1;
            }
        }
    }
    //printGameObjectVector();                                 // ERROR
    //std::cout << "Exited GameField::absorb()\n";               // ERROR
}