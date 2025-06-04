#include "Brick.h"

Brick::Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
    shape.setSize(size);
    shape.setFillColor(color);
    shape.setPosition(position);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);
}

void Brick::Draw(sf::RenderWindow& window) const {
    if (!destroyed)
        window.draw(shape);
}