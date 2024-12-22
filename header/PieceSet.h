#ifndef PIECESET_H
#define PIECESET_H

#include "Piece.h"
#include "Square.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

class PieceSet{
  Piece* pieces[32];
public:
  // constructors
  PieceSet();
  PieceSet(Piece*[]);

  // destructor
  ~PieceSet(){
    for (unsigned i = 0; i < 32; i++) {
      delete pieces[i];
    }
  };
  // delete unused big three function, third one works fine as default
  PieceSet& operator=(const PieceSet&)=delete;
  PieceSet(const PieceSet&)=delete;

  // setters
  void addPiece(Piece*&);
  void removePiece(Piece*&);
  void changePieceTo(Piece * change, int index);

  // getters
  // returns 0 (nullptr) if the piece set doesn't have a piece at the square
  Piece* PieceAt(const Square)const;
  Piece* getPieceAt(int n) {
    return pieces[n];
  }
};

#endif