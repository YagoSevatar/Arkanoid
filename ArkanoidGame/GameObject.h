#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame {
    class GameObject {
    public:
        virtual ~GameObject() = default;
        virtual void Draw(sf::RenderWindow& window) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual sf::FloatRect GetRect() const = 0;
        virtual sf::Vector2f GetPosition() const = 0;

    protected:
        sf::Sprite sprite;
        sf::Texture texture;
    };
}