#pragma once
#include "Player.h"

class Paper : public Player {
public:
    int playAgainst(const Player& other) const override;
    std::unique_ptr<Player> clone() const override;

private:
    int playAgainstRock(const Rock& rock) const override;
    int playAgainstPaper(const Paper& paper) const override;
    int playAgainstScissors(const Scissors& scissors) const override;
};
