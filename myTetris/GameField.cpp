#include "GameField.h"

GameField::GameField(SDL_Renderer* ren, Color c, int unitSize, int winW, int winH)
	: GameObject(ren, FIELD_WIDTH, FIELD_HEIGHT, unitSize)
{
    bgColor = c;
    color = { 0xd3, 0xd3, 0xd3 };

    // calculate position by first converting the window dimensions from pixels to units,
    // performing the calculation, then converting back to pixels
    pos.x = unit * std::abs(((winW / unit) - FIELD_WIDTH) / 2);
    pos.y = unit * std::abs(((winH / unit) - FIELD_HEIGHT) / 2);
    fieldRect.x = pos.x;
    fieldRect.y = pos.y;
    fieldRect.w = FIELD_WIDTH * unit;
    fieldRect.h = FIELD_HEIGHT * unit;

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

void GameField::update() {
    for (int y = 0; y < this->height; y++) {
        int count = 0;
        for (int x = 0; x < this->width; x++) {
            if (pixelVec[y][x]) {
                count++;
            }
        }
        // if line cleared, shift everything down
        if (count == this->width) {
            pixelVec.erase(pixelVec.begin() + y);
            pixelVec.insert(pixelVec.begin(), std::vector<char>(this->width, 0));
        }
    }
}


void GameField::absorb(GameObject piece) {
    std::vector<std::vector<char>> pieceMatrix;
    Position pieceXY = { piece.accessPos().x, piece.accessPos().y };

    pieceXY = translateLocalToGlobal(pieceXY, this->pos);
    pieceMatrix = piece.accessPixelVec();

    // iterate through the piece pixelVec
    for (int i = 0; i < piece.getHeight(); i++) {
        for (int j = 0; j < piece.getWidth(); j++) {
            // record a value where needed
            if (pieceMatrix[i][j]) {
                //std::cout << "copying a block into the field at: [" << i<<"]["<<j<<"]" << std::endl; // ERROR
                //std::cout << "                             into: [" << (pieceXY.y + i) << "][" << (pieceXY.x + j) << "]" << std::endl; // ERROR
                this->pixelVec[pieceXY.y + i][pieceXY.x + j] = 1;
            }
        }
    }
    //printGameObjectVector();        // ERROR
}