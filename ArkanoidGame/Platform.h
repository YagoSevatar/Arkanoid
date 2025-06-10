#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Sprite.h"
namespace ArkanoidGame
{
	class Ball;

    class Platform : public GameObject
    {
    public:
        void Init();
        void Update(float timeDelta) override;  
        void Draw(sf::RenderWindow& window) override;
        sf::FloatRect GetRect() const override { return sprite.getGlobalBounds(); }
        sf::Vector2f GetPosition() const override { return sprite.getPosition(); }
        bool CheckCollisionWithBall(const Ball& ball) const;
        void SetSize(float width, float height) {
            SetSpriteSize(sprite, width, height);
        }
    private:
        void Move(float speed);
    };
}


