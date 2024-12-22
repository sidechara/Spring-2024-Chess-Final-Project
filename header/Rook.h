#ifndef __ROOK_H__
#define __ROOK_H__
#include "Square.h"
#include "Piece.h"
#include <vector>

class Rook : public Piece {
public:
  std::vector<Square> validMoves() override;
  Color getColor() const override {return color;}
  PieceType getType() const override {return ROOK;}
  int getPoints() const override {return 5;}
  // constructor
  Rook(int row, int col, Color team, PieceSet * theSet) {
    this->place.set_row(row);
    this->place.set_col(col);
    this->color = team;
    this->set = theSet;
  }
};

#endif