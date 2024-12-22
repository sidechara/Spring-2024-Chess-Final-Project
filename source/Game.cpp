#include <stdexcept>
#include "../header/Game.h"

Game::Game(){}

Move Game::addMove(Square& starting, Square& ending) { 
  // finds the current piece that is being moved using starting position
  Piece * beingMoved = starting.get_piece();
  // finds current piece being captured
  Piece * capturedPiece = ending.get_piece();

  // determines if there is a captured piece for the pawn promotion part
  bool wasCapturedPiece = false;
  
  if (capturedPiece == nullptr) {
    playedMoves.push_back(Move(starting, ending, beingMoved, nullptr));
  }
  else {
    wasCapturedPiece = true;
    playedMoves.push_back(Move(starting, ending, beingMoved, capturedPiece));
  }
  return playedMoves.back();
}

Move Game::undoMove() {
  if (playedMoves.back().getMovedPiece() == nullptr) {                     // if it was a pawn promotion, last moved piece would be nullptr as set in the PromotePawn function
    playedMoves.pop_back();                                             // remove the "Promotion" placeholder
    back2Pawn(playedMoves.back().getMovedPiece());                      // demote the Promoted Piece back into pawn
  }
  Move lastMove = playedMoves.back();                                   // finds the last move made

  lastMove.getMovedPiece()->setPlace(lastMove.getStartSquare().get_row(), lastMove.getStartSquare().get_col()); // change the moved piece back to it's previous position
  lastMove.getStartSquare().set_piece(lastMove.getMovedPiece());        // changes the previous position square's occupying piece to be the piece that just moved back

  if (lastMove.getCapturedPiece() != nullptr) {                   
    lastMove.getCapturedPiece()->gotUncaptured();                       // if there was a captured piece, set it's death status to false (revive)
    lastMove.getEndSquare().set_piece(lastMove.getCapturedPiece());     // set the square's occupying piece to the revived piece
  }
  else {
    lastMove.getEndSquare().set_piece(nullptr);                         // if there was no piece captured, the end square will now not have an occupying piece
  }
  
  if (lastMove.getMovedPiece()->getType() == PAWN) {
    if ((lastMove.getStartSquare().get_row() == 6) || (lastMove.getStartSquare().get_row() == 1)) {
      Pawn* pawn = dynamic_cast<Pawn*>(lastMove.getMovedPiece());
      pawn->undoMoved();
    }
  }

  playedMoves.pop_back();                                               // the move was never made
  turn = !turn;
  return lastMove;
}

void Game::saveGame(int seconds1,int seconds2,int points1,int points2){
  std::ofstream outFS;
  outFS.open("save.txt");
  outFS << '\n' << seconds1 << ' ' << seconds2 << ' ' << points1 << ' ' << points2;
  if(turn)
    outFS << 'B';
  else
    outFS << 'W';
  for(int i=0;i<8;++i){
    for(int j=0;j<8;++j){
      Piece*possiblePiece=board->getPiece(i,j);
      if(!possiblePiece||possiblePiece->getCaptured())
        outFS << 'p';
      else{
        if(possiblePiece->getColor())
          switch(possiblePiece->getType()){
            case 0:
              outFS << 'W';
              break;
            case 1:
              outFS << 'E';
              break;
            case 2:
              outFS << 'O';
              break;
            case 3:
              outFS << 'S';
              break;
            case 4:
              outFS << 'I';
              break;
            case 5:
              outFS << 'N';
              break;
          }
        else
          switch(possiblePiece->getType()){
            case 0:
              outFS << 'w';
              break;
            case 1:
              outFS << 'e';
              break;
            case 2:
              outFS << 'o';
              break;
            case 3:
              outFS << 's';
              break;
            case 4:
              outFS << 'i';
              break;
            case 5:
              outFS << 'n';
              break;
          }
      }
    }
  }
  outFS.close();
}
int Game::loadSeconds1(const int saveNumber){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int seconds;
  inFS >> seconds;
  return seconds;
}
int Game::loadSeconds2(const int saveNumber){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int seconds;
  char discard;
  inFS >> seconds >> discard >> seconds;
  return seconds;
}
int Game::loadPoints1(const int saveNumber){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int points;
  char discard;
  inFS >> points >> discard >> points >> discard >> points;
  return points;
}
int Game::loadPoints2(const int saveNumber){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int points;
  char discard;
  inFS >> points >> discard >> points >> discard >> points >> discard >> points;
  return points;
}
bool Game::loadTurn(const int saveNumber){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int discardInt;
  char discardChar;
  char readTurn;
  inFS >> discardInt >> discardChar >> discardInt >> discardChar >> discardInt >> discardChar >> discardInt >> readTurn;
  if(readTurn=='W'){
    turn=0;
    return 0;
  }
  else if(readTurn=='B'){
    turn=1;
    return 1;
  }
  else
    throw std::runtime_error("invalid save: no turn identifier");
}
void Game::loadPawns(const int saveNumber,bool color,Piece**pawns){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int discardInt;
  char read;
  char turn;
  inFS >> discardInt >> read >> discardInt >> read >> discardInt >> read >> discardInt >> turn;
  int queenCounter=0,rookCounter=0,bishopCounter=0,knightCounter=0,pawnsLength=0,row=0,col=0;
  if(color){
    for(int i=0;i<64;++i){
      if(pawnsLength==8)
        break;
      row=i%8;
      col=i-row*8;
      inFS>>read;
      switch(read){
        case 'W':
          pawns[pawnsLength++]=new Pawn(row,col,Black,0);
          break;
        case 'E':
          if(++queenCounter>1){
            pawns[pawnsLength++]=new Queen(row,col,Black,0);
            --queenCounter;
          }break;
        case 'O':
          if(++rookCounter>2){
            pawns[pawnsLength++]=new Rook(row,col,Black,0);
            --rookCounter;
          }break;
        case 'S':
          if(++bishopCounter>2){
            pawns[pawnsLength++]=new Bishop(row,col,Black,0);
            --bishopCounter;
          }break;
        case 'I':
          if(++knightCounter>2){
            pawns[pawnsLength++]=new Knight(row,col,Black,0);
            --knightCounter;
          }break;
      }
    }
    while(pawnsLength<8){
      pawns[pawnsLength]=new Pawn(0,0,Black,0);
      pawns[pawnsLength]->gotCaptured();
      pawnsLength++;
    }
  }
  else{
    for(int i=0;i<64;++i){
      if(pawnsLength==8)
        break;
      row=i%8;
      col=i-row*8;
      inFS>>read;
      switch(read){
        case 'w':
          pawns[pawnsLength++]=new Pawn(row,col,White,0);
          break;
        case 'e':
          if(++queenCounter>1){
            pawns[pawnsLength++]=new Queen(row,col,White,0);
            --queenCounter;
          }break;
        case 'o':
          if(++rookCounter>2){
            pawns[pawnsLength++]=new Rook(row,col,White,0);
            --rookCounter;
          }break;
        case 's':
          if(++bishopCounter>2){
            pawns[pawnsLength++]=new Bishop(row,col,White,0);
            --bishopCounter;
          }break;
        case 'i':
          if(++knightCounter>2){
            pawns[pawnsLength++]=new Knight(row,col,White,0);
            --knightCounter;
          }break;
      }
    }
    while(pawnsLength<8){
      pawns[pawnsLength]=new Pawn(0,0,White,0);
      pawns[pawnsLength]->gotCaptured();
      pawnsLength++;
    }
  }
}
void Game::loadNonPawns(const int saveNumber,bool color,Piece**nonPawns){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    throw std::runtime_error("no saved games");
  for (int i=0;i<saveNumber;++i){
    inFS.ignore(999,'\n');
    if(inFS.eof())
      throw std::runtime_error("requested save does not exist");
  }
  int discardInt;
  char read;
  char turn;
  inFS >> discardInt >> read >> discardInt >> read >> discardInt >> read >> discardInt >> turn;
  int queenCounter=0,rookCounter=0,bishopCounter=0,knightCounter=0,nonPawnsLength=0,row=0,col=0;
  if(color){
    for(int i=0;i<64;++i){
      if(nonPawnsLength==8)
        break;
      row=i%8;
      col=i-row*8;
      inFS>>read;
      switch(read){
        case 'E':
          if(++queenCounter<2){
            nonPawns[nonPawnsLength++]=new Queen(row,col,Black,0);
          }break;
        case 'O':
          if(++rookCounter<3){
            nonPawns[nonPawnsLength++]=new Rook(row,col,Black,0);
          }break;
        case 'S':
          if(++bishopCounter<3){
            nonPawns[nonPawnsLength++]=new Bishop(row,col,Black,0);
          }break;
        case 'I':
          if(++knightCounter<3){
            nonPawns[nonPawnsLength++]=new Knight(row,col,Black,0);
          }break;
      }
    }
    while(nonPawnsLength<8){
      nonPawns[nonPawnsLength]=new Pawn(0,0,Black,0);
      nonPawns[nonPawnsLength]->gotCaptured();
      nonPawnsLength++;
    }
  }
  else{
    for(int i=0;i<64;++i){
      if(nonPawnsLength==8)
        break;
      row=i%8;
      col=i-row*8;
      inFS>>read;
      switch(read){
        case 'e':
          if(++queenCounter<2){
            nonPawns[nonPawnsLength++]=new Queen(row,col,White,0);
          }break;
        case 'o':
          if(++rookCounter<3){
            nonPawns[nonPawnsLength++]=new Rook(row,col,White,0);
          }break;
        case 's':
          if(++bishopCounter<3){
            nonPawns[nonPawnsLength++]=new Bishop(row,col,White,0);
          }break;
        case 'i':
          if(++knightCounter<3){
            nonPawns[nonPawnsLength++]=new Knight(row,col,White,0);
          }break;
      }
    }
    while(nonPawnsLength<8){
      nonPawns[nonPawnsLength]=new Pawn(0,0,White,0);
      nonPawns[nonPawnsLength]->gotCaptured();
      nonPawnsLength++;
    }
  }
}
void Game::sortNonPawns(Piece*nonPawns[]){
  Piece*tempArray[8];
  int capturedCounter=0;
  int capturedFound=0;
  // rook1
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==2){
      tempArray[0]=nonPawns[i];
      break;
    }
  if(!tempArray[0])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        tempArray[0]=nonPawns[i];
        ++capturedCounter;
        break;
      }
  // knight1
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==4){
      tempArray[1]=nonPawns[i];
      break;
    }
  if(!tempArray[1])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        if(capturedCounter==capturedFound){
          tempArray[1]=nonPawns[i];
          ++capturedCounter;
          break;
        }else capturedFound++;
      }
  capturedFound=0;
  // bishop1
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==3){
      tempArray[2]=nonPawns[i];
      break;
    }
  if(!tempArray[2])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        if(capturedCounter==capturedFound){
          tempArray[2]=nonPawns[i];
          ++capturedCounter;
          break;
        }else capturedFound++;
      }
  capturedFound=0;
  // queen
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==1){
      tempArray[3]=nonPawns[i];
      break;
    }
  if(!tempArray[3])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        if(capturedCounter==capturedFound){
          tempArray[3]=nonPawns[i];
          ++capturedCounter;
          break;
        }else capturedFound++;
      }
  capturedFound=0;
  // king
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==5){
      tempArray[4]=nonPawns[i];
      break;
    }
  // bishop2
  int bishopCounter=0;
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==3){
      if(bishopCounter++==1){
        tempArray[5]=nonPawns[i];
        break;
      }
    }
  if(!tempArray[5])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        if(capturedCounter==capturedFound){
          tempArray[5]=nonPawns[i];
          ++capturedCounter;
          break;
        }else capturedFound++;
      }
  capturedFound=0;
  // knight2
  int knightCounter=0;
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==4){
      if(knightCounter++==1){
        tempArray[6]=nonPawns[i];
        break;
      }
    }
  if(!tempArray[6])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        if(capturedCounter==capturedFound){
          tempArray[6]=nonPawns[i];
          ++capturedCounter;
          break;
        }else capturedFound++;
      }
  capturedFound=0;
  // rook2
  int rookCounter=0;
  for(int i=0;i<8;++i)
    if(nonPawns[i]->getType()==2){
      if(rookCounter++==1){
        tempArray[7]=nonPawns[i];
        break;
      }
    }
  if(!tempArray[7])
    for(int i=0;i<8;++i)
      if(nonPawns[i]->getType()==0){
        if(capturedCounter==capturedFound){
          tempArray[7]=nonPawns[i];
          ++capturedCounter;
          break;
        }else capturedFound++;
      }
  nonPawns=tempArray;
}
Board*Game::loadGame(const int saveNumber){
  loadTurn(saveNumber);
  Piece*loadedPieceArray[32];

  Piece*blackNonPawns[8];
  loadNonPawns(saveNumber,1,blackNonPawns);
  sortNonPawns(blackNonPawns);
  for(int i=0;i<8;++i)
    loadedPieceArray[i]=blackNonPawns[i];

  Piece*blackPawns[8];
  loadPawns(saveNumber,1,blackPawns);
  for(int i=0;i<8;++i)
    loadedPieceArray[i+8]=blackPawns[i];

  Piece*whitePawns[8];
  loadPawns(saveNumber,0,whitePawns);
  for(int i=0;i<8;++i)
    loadedPieceArray[i+16]=whitePawns[i];

  Piece*whiteNonPawns[8];
  loadNonPawns(saveNumber,0,whiteNonPawns);
  sortNonPawns(whiteNonPawns);
  for(int i=0;i<8;++i)
    loadedPieceArray[i+24]=whiteNonPawns[i];

  PieceSet*loadedSet=new PieceSet(loadedPieceArray);
  for(int i=0;i<32;++i)
    loadedPieceArray[i]->setSet(loadedSet);
  delete board;
  board=new Board(*loadedSet);
  return board;
}

bool Game::isPawnPromotion(Move after) {
  Piece * potentialPawn = after.getMovedPiece();

  if (potentialPawn->getType() != PAWN) {                        // check that the piece is a pawn
    return false;
  }

  if (potentialPawn->getColor() == White) {                      // check for white pawn
    if (potentialPawn->getPlace().get_row() == 0) {                // check that the white pawn is in the end row
      return true;
    }
  }
  else {                                                         // check for black pawn
    if (potentialPawn->getPlace().get_row() == 7) {                // check that the black pawn in the the end row
      return true;
    }
  }
  return false;
}

Piece* Game::PromotePawn(Piece * pawn, PieceType changeInto) {
  int atIndex = pawn->getPieceSetIndex();                                              // finds index of specific pawn within the pieceset

  PieceSet * currentSet = pawn->getSet();                                             // keep track of the current set

  Square& thePlace = pawn->getPlace();                                                 // store the contructor arguments for new created piece
  int theRow = thePlace.get_row();
  int theCol = thePlace.get_col();
  Color theColor = pawn->getColor();

  delete pawn->getSet()->getPieceAt(atIndex);                                         // remove the pawn piece so it can be replaced
  playedMoves.back().setMovedPiece(nullptr);                                          // prevent dangling pointer
  Piece * newPromotionPiece = nullptr;

  if (changeInto == KNIGHT) {                                                         // change into a knight
    newPromotionPiece = new Knight(theRow, theCol, theColor, currentSet);             // construct new piece
  }
  else if (changeInto == BISHOP) {                                                    // change into bishop
    newPromotionPiece = new Bishop(theRow, theCol, theColor, currentSet);             // construct new piece
  }
  else if (changeInto == ROOK) {                                                      // change into rook 
    newPromotionPiece = new Rook(theRow, theCol, theColor, currentSet);               // construct new piece
  }
  else {                                                                              // change into queen
    newPromotionPiece = new Queen(theRow, theCol, theColor, currentSet);              // construct new piece
  }
  currentSet->changePieceTo(newPromotionPiece, atIndex);                              // replace the previous pawn with newly constructed piece
  board->getSquare(theRow, theCol).set_piece(newPromotionPiece);                      // point the previous occupied square to the new piece created

  playedMoves.back().setMovedPiece(newPromotionPiece);                                // updating the piece in the last move to the newly promoted pieceType
  playedMoves.push_back(playedMoves.back());                                          
  playedMoves.back().setMovedPiece(nullptr);                                          // push a null piece move to the back (used in undo for reverting back to Pawn)

  return newPromotionPiece;
}

void Game::back2Pawn(Piece *pieceGoingBack) {
  int atIndex = pieceGoingBack->getPieceSetIndex();                                    // finds index of specific pawn within the pieceset

  PieceSet * currentSet = pieceGoingBack->getSet();                                   // keep track of the current set

  Square thePlace = pieceGoingBack->getPlace();                                       // store the contructor arguments for new created piece
  int theRow = thePlace.get_row();  
  int theCol = thePlace.get_col();
  Color theColor = pieceGoingBack->getColor();

  delete pieceGoingBack->getSet()->getPieceAt(atIndex);                               // remove the Current Piece
  playedMoves.back().setMovedPiece(nullptr);                                          // prevent dangling pointer

  Piece * newDemotionPiece = new Pawn(theRow, theCol, theColor, currentSet);          // construct new piece
  currentSet->changePieceTo(newDemotionPiece, atIndex);                               // replace the previous pawn

  board->getSquare(theRow, theCol).set_piece(newDemotionPiece);                      // point the previous occupied square to the new piece created
                                                 
  playedMoves.back().setMovedPiece(newDemotionPiece);                                 // reset back to a pawn in the played moves
}