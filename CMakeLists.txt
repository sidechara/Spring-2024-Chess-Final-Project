cmake_minimum_required(VERSION 3.2)
project(chess-tests)

add_subdirectory(googletest)

add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-g;-O0>")

add_executable(tests source/test-code/pieces-test.cpp source/test-code/board-test.cpp source/test-code/pieceset-test.cpp
source/Board.cpp source/PieceSet.cpp source/Piece.cpp source/Square.cpp source/King.cpp source/Queen.cpp source/Rook.cpp source/Bishop.cpp source/Knight.cpp source/Pawn.cpp source/Game.cpp source/Move.cpp)

target_link_libraries(tests gtest)