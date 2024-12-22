#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "Square.h"
#include "Piece.h"
#include <vector>

class Bishop : public Piece {
public:
  std::vector<Square> validMoves() override;
  Color getColor() const override {return color;}
  PieceType getType() const override {return BISHOP;}
  int getPoints() const override{return 3;}
  // constructor
  Bishop(int row, int col, Color team, PieceSet * theSet){
    this->place.set_row(row);
    this->place.set_col(col);
    this->color = team;
    this->set = theSet;
  }
};
#endif