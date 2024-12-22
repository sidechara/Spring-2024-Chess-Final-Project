#ifndef __COMPUTER_PLAYER_H__
#define __COMPUTER_PLAYER_H__
#include "PieceSet.h"

class ComputerPlayer {
  PieceSet* set;
  Piece* moved;
public:
  ComputerPlayer(PieceSet*);
  Square makeMove();
  Piece* getMoved(){return moved;}
};

#endif