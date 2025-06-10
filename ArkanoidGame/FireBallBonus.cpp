#include "FireBallBonus.h"

namespace ArkanoidGame
{
    FireBallBonus::FireBallBonus(const sf::Vector2f& position, Ball& ball)
        : Bonus(Type::FireBall, position), ball(ball),
        originalSpeed(0), originalPiercing(false)
    {
    }

    void FireBallBonus::Apply()
    {
        if (!applied) {
            originalSpeed = ball.GetSpeed();
            originalPiercing = ball.IsPiercing();
            ball.SetSpeed(originalSpeed * 1.5f);
            ball.SetPiercing(true);
            ball.SetColor(sf::Color::Red);
            applied = true;
        }
    }

    void FireBallBonus::Remove()
    {
        if (applied) {
            ball.SetSpeed(originalSpeed);
            ball.SetPiercing(originalPiercing);
            ball.ResetColor();
        }
    }
   
}