#ifndef __PAWN_H__
#define __PAWN_H__
#include "Square.h"
#include "Piece.h"
#include <vector>

class Pawn : public Piece {
  bool moved = false;
public:
  std::vector<Square> validMoves() override;
  Color getColor() const override {return color;}
  PieceType getType() const override {return PAWN;}
  int getPoints() const override {return 1;}
  // constructor
  Pawn(int row, int col, Color team, PieceSet * theSet){
    this->place.set_row(row);
    this->place.set_col(col);
    this->color = team;
    this->set = theSet;
  }
  void undoMoved(){moved=false;}
};

#endif