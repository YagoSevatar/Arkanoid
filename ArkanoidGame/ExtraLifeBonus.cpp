#include "ExtraLifeBonus.h"
#include "Application.h"

namespace ArkanoidGame
{
    ExtraLifeBonus::ExtraLifeBonus(const sf::Vector2f& position)
        : Bonus(Type::ExtraLife, position)
    {
    }

    void ExtraLifeBonus::Apply()
    {
        Application::Instance().GetGame().AddLife();
    }
}