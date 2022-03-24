#pragma once
#include "GameObject.h"
#include "GamePiece.h"

/* PiecePreview class
 * a piecePreview object is a box that displays a piece
 * For example, the held piece will be displayed as PiecePreview object
 * and so will the upcoming pieces on the pieces queue
 */
class PiecePreview {
public:
    PiecePreview();
    PiecePreview(Position p, GamePiece* gamePiece, SDL_Renderer* r);
    PiecePreview(Position p, GamePiece* gamePiece, SDL_Renderer* r, const char* t);

    void setPiece(GamePiece* gp) { piece = gp; }

    Position& accessPos() { return pos; }

    void render();

private:
    Position pos;
    GamePiece* piece;
    Color color = { 20,20,20 };
    SDL_Rect rect;
    SDL_Renderer* renderer;
    const char* title;
};