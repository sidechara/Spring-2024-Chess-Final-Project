#ifndef __KING_H__
#define __KING_H__
#include "Square.h"
#include "Piece.h"
#include <vector>

class King : public Piece {
public:
  std::vector<Square> validMoves() override;
  Color getColor() const override {return color;}
  PieceType getType() const override {return KING;}
  int getPoints() const override {return 0;}
  // constructor
  King(int row, int col, Color team, PieceSet * theSet){
    this->place.set_row(row);
    this->place.set_col(col);
    this->color = team;
    this->set = theSet;
  }    
};
#endif