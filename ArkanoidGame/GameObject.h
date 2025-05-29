#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class GameObject
    {
    public:
        virtual ~GameObject() = default;

        virtual void Draw(sf::RenderWindow& window);
        virtual void Update(float deltaTime) = 0;

        const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
        const sf::FloatRect& GetRect() const { return sprite.getGlobalBounds(); }

    protected:
        sf::Sprite sprite;
        sf::Texture texture;
    };
}