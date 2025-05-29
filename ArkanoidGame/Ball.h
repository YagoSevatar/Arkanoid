#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
    class Ball : public GameObject
    {
    public:
        void Init();
        void Update(float timeDelta) override;
        void HandleBoundaryCollisions();
        void ReboundFromPlatform(const sf::Vector2f& platformPosition, float platformWidth);
        void ReboundFromBrick(const sf::FloatRect& brickRect);
        const sf::Vector2f& GetDirection() const { return direction; }
        void SetPosition(const sf::Vector2f& position);
    private:
        sf::Vector2f direction;
        void NormalizeDirection();
        void Reflect(const sf::Vector2f& normal);
    };
}