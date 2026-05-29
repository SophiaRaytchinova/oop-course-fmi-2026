#include "RPSGame.h"

size_t RPSGame::simulateDuel(size_t firstPlayerIndex, size_t secondPlayerIndex) const {
    if (firstPlayerIndex == secondPlayerIndex) {
        return 0;
    }
    return items[firstPlayerIndex]->playAgainst(*items[secondPlayerIndex]);
}

size_t RPSGame::simulateTournament() const {
    int maxResult = INT_MIN;
    size_t winnerIndex = 0;
    for (size_t i = 0; i < items.size(); i++) {
        int currentResult = 0;
        for (size_t j = 0; j < items.size(); j++) {
            currentResult += simulateDuel(i, j);
        }

        if (currentResult > maxResult) {
            winnerIndex = i;
            maxResult = currentResult;
        }
    }
    return winnerIndex;
}
