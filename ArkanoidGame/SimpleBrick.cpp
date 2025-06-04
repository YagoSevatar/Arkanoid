#include "SimpleBrick.h"

SimpleBrick::SimpleBrick(const sf::Vector2f& position,
    const sf::Vector2f& size,
    const sf::Color& color)
    : Brick(position, size, color) {
}

bool SimpleBrick::OnHit() {
    Destroy();
    return true;
}