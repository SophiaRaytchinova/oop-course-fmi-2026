#pragma once
#include <memory>

class Rock;
class Paper;
class Scissors;

class Player {
public:
    // playAgainst will return:
    // 1 if the caller of the function wins
    // -1 if the caller of the function loses
    // 0 if it's a draw
    virtual int playAgainst(const Player& other) const = 0;
    virtual ~Player() = default;
    virtual std::unique_ptr<Player> clone() const = 0;

protected:
    virtual int playAgainstRock(const Rock& rock) const = 0;
    virtual int playAgainstPaper(const Paper& paper) const = 0;
    virtual int playAgainstScissors(const Scissors& scissors) const = 0;

private:

    friend class Rock;
    friend class Paper;
    friend class Scissors;

};
