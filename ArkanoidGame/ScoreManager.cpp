#include "ScoreManager.h"
#include <algorithm>

namespace ArkanoidGame {
    void ScoreManager::AddObserver(IScoreObserver* observer) {
        observers.push_back(observer);
    }

    void ScoreManager::RemoveObserver(IScoreObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void ScoreManager::NotifyScoreChanged(int newScore) {
        for (auto* observer : observers) {
            observer->OnScoreChanged(newScore);
        }
    }

    void ScoreManager::AddScore(int points) {
        currentScore += points;
        NotifyScoreChanged(currentScore);
    }
}