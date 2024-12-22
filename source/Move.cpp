#include "../header/Move.h"

Piece* Move::getCapturedPiece(){
    return capturedPiece;
}

Piece* Move::getMovedPiece(){
    return piece;
}

Square& Move::getStartSquare(){
    return startSquare;
}

Square& Move::getEndSquare(){
    return endSquare;
}