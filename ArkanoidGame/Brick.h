#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
    virtual ~Brick() = default;

    virtual bool OnHit() = 0;
    virtual void Draw(sf::RenderWindow& window) const;

    bool IsDestroyed() const { return destroyed; }
    void Destroy() { destroyed = true; }
    const sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }
    virtual sf::Vector2f GetPosition() const { return shape.getPosition(); }
protected:
    sf::RectangleShape shape;
    bool destroyed = false;
};