#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
public:
    Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);

    void Draw(sf::RenderWindow& window) const;
    bool IsDestroyed() const { return destroyed; }
    void Destroy() { destroyed = true; }
    const sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }

private:
    sf::RectangleShape shape;
    bool destroyed = false;
};