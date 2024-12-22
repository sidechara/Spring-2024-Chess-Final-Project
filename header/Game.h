#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <string>
#include <fstream>
#include "Move.h"
#include "Board.h"

enum CheckStatus {
  None, WhiteInCheck, BlackInCheck, WhiteCheckmated, BlackCheckmated
};

enum Result {
  WhiteWin, BlackWin, Draw
};

class Game {
    std::vector<Move> playedMoves;
    bool turn = 0;
    Result result;
    CheckStatus checkStatus;
    Board* board;
public:
    Game();
    void isEnded(); //void?
    void isChecked();
    void operation();
    Move addMove(Square&, Square&);
    Move undoMove();
    void isCheckmated();
    void saveGame(int seconds1,int seconds2,int points1,int points2);
    int loadSeconds1(const int saveNumber);
    int loadSeconds2(const int saveNumber);
    int loadPoints1(const int saveNumber);
    int loadPoints2(const int saveNumber);
    bool loadTurn(const int saveNumber);
    Board*loadGame(const int saveNumber);
    bool getTurn(){return turn;};
    void switchTurn(){turn=!turn;};
    bool isPawnPromotion(Move);
    Piece* PromotePawn(Piece *, PieceType);
    void back2Pawn(Piece *);
    void setBoard(Board* b){board = b;}
private:
    void loadPawns(const int saveNumber,bool color,Piece*pawns[]);
    void loadNonPawns(const int saveNumber,bool color,Piece*pawns[]);
    void sortNonPawns(Piece*pawns[]);
};

#endif