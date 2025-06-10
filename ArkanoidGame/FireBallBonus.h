#pragma once
#include "Bonus.h"
#include "Ball.h"

namespace ArkanoidGame
{
    class FireBallBonus : public Bonus
    {
    public:
        FireBallBonus(const sf::Vector2f& position, Ball& ball);
        void Apply() override;
        void Remove() override;
      
    private:
        Ball& ball;
        float originalSpeed;
        bool originalPiercing;
        float duration = 5.0f;
        float elapsedTime = 0.0f;
        bool applied = false;
    };
}