#include "Scissors.h"

int Scissors::playAgainst(const Player& other) const {
    return -1 * (other.playAgainstScissors(*this));
}

int Scissors::playAgainstRock(const Rock& rock) const {
    return -1;
}

int Scissors::playAgainstPaper(const Paper& paper) const {
    return 1;
}

int Scissors::playAgainstScissors(const Scissors& scissors) const {
    return 0;
}

std::unique_ptr<Player> Scissors::clone() const {
    return std::make_unique<Scissors>(*this);
}
