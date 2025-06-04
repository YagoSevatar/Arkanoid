#pragma once
#include "Brick.h"
#include <vector>

class DurableBrick : public Brick
{
public:
    DurableBrick(const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::vector<sf::Color>& damageColors);

    bool OnHit() override;
    void Draw(sf::RenderWindow& window) const override;
    int GetHitPoints() const { return hitPoints; }

private:
    int hitPoints;
    std::vector<sf::Color> damageColors;
    mutable sf::RectangleShape durabilityIndicator;
};