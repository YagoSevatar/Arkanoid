#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    class Ball : public GameObject
    {
    public:
        void Init();
        void Update(float timeDelta) override;
        void Draw(sf::RenderWindow& window) override;
        void HandleBoundaryCollisions();
        sf::FloatRect GetRect() const override { return sprite.getGlobalBounds(); }
        sf::Vector2f GetPosition() const override { return sprite.getPosition(); }
        void ReboundFromPlatform(const sf::Vector2f& platformPosition, float platformWidth);
        void ReboundFromBrick(const sf::FloatRect& brickRect);
        const sf::Vector2f& GetDirection() const { return direction; }
        void SetPosition(const sf::Vector2f& position);
        void SetSpeed(float newSpeed) { speed = newSpeed; }
        float GetSpeed() const { return speed; }
        void SetPiercing(bool piercing) { isPiercing = piercing; }
        bool IsPiercing() const { return isPiercing; }
        void SetColor(const sf::Color& color) { sprite.setColor(color); }
        void ResetColor() { sprite.setColor(sf::Color::White); }
    private:
        sf::Vector2f direction;
        void NormalizeDirection();
        void Reflect(const sf::Vector2f& normal);
        float speed = BALL_SPEED;
        bool isPiercing = false;

    };
}