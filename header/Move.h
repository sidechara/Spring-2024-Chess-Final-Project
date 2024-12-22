#ifndef __MOVE_H__
#define __MOVE_H__
#include "Piece.h"
#include "Square.h"
#include <assert.h>

class Move {
  Square& startSquare;
  Square& endSquare;
  Piece* piece;
  Piece* capturedPiece;
public:
  Move(Square& start, Square& end, Piece* current, Piece* captured) : startSquare(start), endSquare(end), piece(current), capturedPiece(captured) {}
  Piece* getCapturedPiece();
  Piece* getMovedPiece();
  Square& getStartSquare();
  Square& getEndSquare();
  void setMovedPiece(Piece * newPiece) { piece = newPiece;}
};

#endif