#include "DurableBrick.h"
#include <cassert>

DurableBrick::DurableBrick(const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::vector<sf::Color>& damageColors)
    : Brick(position, size, damageColors.back()),
    damageColors(damageColors),
    hitPoints(static_cast<int>(damageColors.size()))
{
    assert(!damageColors.empty());

    durabilityIndicator.setSize(sf::Vector2f(size.x - 4.f, 4.f));
    durabilityIndicator.setPosition(position.x + 2.f, position.y + 2.f);
    durabilityIndicator.setFillColor(sf::Color::White);
}

bool DurableBrick::OnHit()
{
    if (IsDestroyed()) return false;

    if (--hitPoints <= 0)
    {
        Destroy();
        return true;
    }

    if (!damageColors.empty())
    {
        int colorIndex = static_cast<int>(damageColors.size()) - hitPoints;
        colorIndex = std::clamp(colorIndex, 0, static_cast<int>(damageColors.size()) - 1);
        shape.setFillColor(damageColors[colorIndex]);
    }

    return false;
}

void DurableBrick::Draw(sf::RenderWindow& window) const
{
    if (!IsDestroyed())
    {
        Brick::Draw(window);

        if (hitPoints < static_cast<int>(damageColors.size()))
        {
            float ratio = static_cast<float>(hitPoints) / damageColors.size();
            float width = (shape.getSize().x - 4.f) * ratio;
            durabilityIndicator.setSize(sf::Vector2f(width, 4.f));
            window.draw(durabilityIndicator);
        }
    }
}