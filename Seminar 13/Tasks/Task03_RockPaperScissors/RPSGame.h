#pragma once
#include <iostream>
#include "Player.h"
#include "PolymorphicContainer.hpp"

// basically the game class is a polymorphic container of players,
// and we can add a simulate tournament method on top of that
class RPSGame : public PolymorphicContainer<Player> {
public:
    size_t simulateTournament() const;
private:
    size_t simulateDuel(size_t firstPlayerIndex, size_t secondPlayerIndex) const;
};
