#pragma once
#include <vector>
#include "IScoreObserver.h"

namespace ArkanoidGame {
    class ScoreManager {
    public:
        void AddObserver(IScoreObserver* observer);
        void RemoveObserver(IScoreObserver* observer);
        void NotifyScoreChanged(int newScore);
        void AddScore(int points);
        int GetCurrentScore() const { return currentScore; }

    private:
        std::vector<IScoreObserver*> observers;
        int currentScore = 0;
    };
}