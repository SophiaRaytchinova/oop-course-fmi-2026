#include "Rock.h"

int Rock::playAgainst(const Player& other) const {
    return -1 * (other.playAgainstRock(*this));
}

int Rock::playAgainstRock(const Rock& rock) const {
    return 0;
}

int Rock::playAgainstPaper(const Paper& paper) const {
    return -1;
}

int Rock::playAgainstScissors(const Scissors& scissors) const {
    return 1;
}

std::unique_ptr<Player> Rock::clone() const {
    return std::make_unique<Rock>(*this);
}
