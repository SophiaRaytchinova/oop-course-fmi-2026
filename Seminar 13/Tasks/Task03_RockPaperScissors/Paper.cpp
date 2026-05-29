#include "Paper.h"

int Paper::playAgainst(const Player& other) const {
    return -1 * (other.playAgainstPaper(*this));
}

int Paper::playAgainstRock(const Rock& rock) const {
    return 1;
    // or alternatively return -(rock->playAgainstScissors(this));
    // but you have to make sure that at least one side has implementation
    // so that the other side can reuse it
}

int Paper::playAgainstPaper(const Paper& paper) const {
    return 0;
}

int Paper::playAgainstScissors(const Scissors& scissors) const {
    return -1;
}

std::unique_ptr<Player> Paper::clone() const {
    return std::make_unique<Paper>(*this);
}
