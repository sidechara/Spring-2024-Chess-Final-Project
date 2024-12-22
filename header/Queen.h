#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "Square.h"
#include "Piece.h"
#include <vector>

class Queen : public Piece {
public:
  std::vector<Square> validMoves() override;
  Color getColor() const override {return color;}
  PieceType getType() const override {return QUEEN;}
  int getPoints() const override {return 9;}
  // constructor
  Queen(int row, int col, Color team, PieceSet * theSet){
    this->place.set_row(row);
    this->place.set_col(col);
    this->color = team;
    this->set = theSet;
  }
};

#endif