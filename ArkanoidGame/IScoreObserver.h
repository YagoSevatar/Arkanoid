#pragma once

class IScoreObserver {
public:
    virtual ~IScoreObserver() = default;
    virtual void OnScoreChanged(int newScore) = 0;
};