#ifndef BOARD_H
#define BOARD_H

#include "PieceSet.h"
#include "Square.h"
#include <string>

class Board{
  Square board[8][8];
  PieceSet pieceSet;
public:
  Board();
  Board(PieceSet& load);
  Piece* getPiece(int, int);
  int movePiece(int, int, int, int);
  bool isInCheck(bool);
  bool hasNoLegalMoves(bool);
  Square& getSquare(int row, int col){return board[row][col];};
  PieceSet* getSet(){return &pieceSet;}
};
#endif