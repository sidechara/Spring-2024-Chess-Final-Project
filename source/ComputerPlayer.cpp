#include "../header/ComputerPlayer.h"
#include <ctime>
#include <cstdlib>

ComputerPlayer::ComputerPlayer(PieceSet* theSet) : set(theSet) {}

Square ComputerPlayer::makeMove() {
    std::srand(std::time(nullptr));
    int random = std::rand()%16;
    //check it's not captured
    moved = set->getPieceAt(random);
    std::vector<Square> valid = moved->validMoves();
    while (moved->getCaptured() || valid.size() == 0) {
        random = std::rand()%16;
        moved = set->getPieceAt(random);
        valid = moved->validMoves();
    }
    int randMove = std::rand()%(valid.size());
    return valid.at(randMove);
}