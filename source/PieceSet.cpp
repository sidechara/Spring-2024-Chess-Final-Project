#include "../header/PieceSet.h"
// #define NDEBUG
#include <assert.h>

PieceSet::PieceSet(){
  pieces[0]=new Rook(0,0,Black,this);
  pieces[1]=new Knight(0,1,Black,this);
  pieces[2]=new Bishop(0,2,Black,this);
  pieces[3]=new Queen(0,3,Black,this);
  pieces[4]=new King(0,4,Black,this);
  pieces[5]=new Bishop(0,5,Black,this);
  pieces[6]=new Knight(0,6,Black,this);
  pieces[7]=new Rook(0,7,Black,this);
  for(int i=8;i<16;++i){
    pieces[i]=new Pawn(1,i-8,Black,this);
    pieces[i+8]=new Pawn(6,i-8,White,this);
  }
  pieces[24]=new Rook(7,0,White,this);
  pieces[25]=new Knight(7,1,White,this);
  pieces[26]=new Bishop(7,2,White,this);
  pieces[27]=new Queen(7,3,White,this);
  pieces[28]=new King(7,4,White,this);
  pieces[29]=new Bishop(7,5,White,this);
  pieces[30]=new Knight(7,6,White,this);
  pieces[31]=new Rook(7,7,White,this);
}
PieceSet::PieceSet(Piece* newPieces[]){
  for(int i=0;i<32;++i)
    pieces[i]=newPieces[i];
}

void PieceSet::addPiece(Piece*&toAdd){
  for(int i=0;i<32;++i)
    if(pieces[i]==toAdd){
      pieces[i]->gotUncaptured();
      return;
    }
  assert(false&&"Piece to add to piece set does not exist");
}

void PieceSet::removePiece(Piece*&toDelete){
  for(int i=0;i<32;++i)
    if(pieces[i]==toDelete){
      pieces[i]->gotCaptured();
      return;
    }
  assert(false&&"Piece to remove from piece set does not exist");
}

Piece* PieceSet::PieceAt(const Square query)const{
  for(int i=0;i<32;++i)
    if (pieces[i] != nullptr) {
      if(pieces[i]->getPlace().get_row()==query.get_row()&&
       pieces[i]->getPlace().get_col()==query.get_col())
      if (pieces[i]->getCaptured() == false) return pieces[i];
    }
  return 0;
}

void PieceSet::changePieceTo(Piece * change, int place) {
  pieces[place] = change;
}