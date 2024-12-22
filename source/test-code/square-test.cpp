#include <iostream>
#include "gtest/gtest.h"
#include "../../header/Board.h"
#include "../../header/Game.h"

TEST(SquareTests, SquareDefaultConstructor) {
  Square def;
  EXPECT_EQ(0,def.get_row());
}

TEST(SquareTests, SquareParameterizedConstructor) {
  Square def(7,7);
  EXPECT_EQ(7,def.get_row());
}

TEST(SquareTests, CurrentPiece) {
  Square def;
  EXPECT_EQ(nullptr,def.get_piece());
}

TEST(SquareTests, SquareSetters) {
  Square def;
  def.set_row(7);
  def.set_col(7);
  EXPECT_EQ(14,def.get_col()+def.get_row()); 
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}