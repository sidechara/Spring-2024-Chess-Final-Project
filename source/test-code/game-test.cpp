#include "gtest/gtest.h"
#include "../../header/Board.h"
#include "../../header/Game.h"

TEST(GameTest, addMovefunction) {
  Game gameTest;
  Rook * rook = new Rook(2, 6, Black, nullptr);
  Square begin(2, 6, rook); 
  Square end(6, 6, nullptr);

  Move madeMove = gameTest.addMove(begin, end);
  Move testMove(begin, end, rook, nullptr);

  EXPECT_EQ(madeMove.getCapturedPiece(), testMove.getCapturedPiece());
  EXPECT_EQ(madeMove.getMovedPiece(), testMove.getMovedPiece());
  EXPECT_EQ(madeMove.getStartSquare(), testMove.getStartSquare());
  EXPECT_EQ(madeMove.getEndSquare(), testMove.getEndSquare());

  delete rook;
}
TEST(GameTest, undoMovefunction) {
  Game undoTest;
  Queen * whiteQueen = new Queen(0, 0, White, nullptr);
  Queen * blackQueen = new Queen(7, 7, Black, nullptr);
  
  Move move1 = undoTest.addMove(Square(whiteQueen->getPlace().get_row(), whiteQueen->getPlace().get_col(), whiteQueen), Square(1, 1, nullptr));
  Move move2 = undoTest.addMove(Square(blackQueen->getPlace().get_row(), blackQueen->getPlace().get_col(), blackQueen), Square(6, 6, nullptr));
  Move move3 = undoTest.addMove(Square(whiteQueen->getPlace().get_row(), whiteQueen->getPlace().get_col(), whiteQueen), Square(2, 2, nullptr));

  Move undoLastMove = undoTest.undoMove();

  EXPECT_EQ(undoLastMove.getCapturedPiece(), move2.getCapturedPiece());
  EXPECT_EQ(undoLastMove.getMovedPiece(), move2.getMovedPiece());
  EXPECT_EQ(undoLastMove.getStartSquare(), move2.getStartSquare());
  EXPECT_EQ(undoLastMove.getEndSquare(), move2.getEndSquare());
  EXPECT_EQ(whiteQueen->getPlace().get_row(), 1);
  EXPECT_EQ(whiteQueen->getPlace().get_col(), 1);

  delete whiteQueen;
  delete blackQueen;
}

TEST(GameTest, PawnPromotingChecker) {
  Game gameCheckPromotion;
  
  Pawn * pawn = new Pawn(1, 4, White, nullptr);
  Square begin(1, 4, pawn);
  Square end(0, 4, nullptr);
  
  Move movePawn = gameCheckPromotion.addMove(begin, end);
  
  EXPECT_TRUE(gameCheckPromotion.isPawnPromotion(movePawn));

  delete pawn;
}