#pragma once
#include "Brick.h"

class SimpleBrick : public Brick {
public:
    SimpleBrick(const sf::Vector2f& position,
        const sf::Vector2f& size,
        const sf::Color& color);

    bool OnHit() override;
};