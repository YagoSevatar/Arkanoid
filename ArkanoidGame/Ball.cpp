#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>
#include "Platform.h"
#include <cmath>

namespace
{
    const std::string TEXTURE_ID = "ball";
}

namespace ArkanoidGame
{
    void Ball::Init()
    {
        assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

        InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
        sprite.setPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f });

      
        const float angle = 30.f + rand() % 120;
        const float radians = angle * 3.14159265f / 180.f;
        direction.x = std::cos(radians);
        direction.y = -std::sin(radians); 
        NormalizeDirection();
    }

    void Ball::Update(float timeDelta)
    {
        sf::Vector2f movement;
        movement.x = direction.x * BALL_SPEED * timeDelta;
        movement.y = direction.y * BALL_SPEED * timeDelta;
        sprite.move(movement);

        HandleBoundaryCollisions();
    }

    void Ball::HandleBoundaryCollisions()
    {
        const float radius = BALL_SIZE / 2.0f;
        const sf::Vector2f pos = sprite.getPosition();

        if (pos.x < radius) {
            Reflect({ 1.0f, 0.0f });
            sprite.setPosition(radius, pos.y);
        }

        else if (pos.x > SCREEN_WIDTH - radius) {
            Reflect({ -1.0f, 0.0f });
            sprite.setPosition(SCREEN_WIDTH - radius, pos.y);
        }

        if (pos.y < radius) {
            Reflect({ 0.0f, 1.0f });
            sprite.setPosition(pos.x, radius);
        }
    }

    void Ball::ReboundFromPlatform(const sf::Vector2f& platformPos, float platformWidth) {
     
        float hitPos = ((GetPosition().x - platformPos.x) / platformWidth) * 2.0f - 1.0f;
        hitPos = std::clamp(hitPos, -0.8f, 0.8f);
        float directionInfluence = 0.3f * (direction.x > 0 ? 1 : -1);
        float reboundAngle = (hitPos + directionInfluence) * (70.0f * 3.14159f / 180.0f);
        direction.x = sin(reboundAngle);
        direction.y = -cos(reboundAngle);
        sf::Vector2f newPos = GetPosition();
        newPos.y = platformPos.y - BALL_SIZE / 2 - 1.0f;
        SetPosition(newPos);
    }

    void Ball::ReboundFromBrick(const sf::FloatRect& brickRect)
    {
      
        sf::FloatRect ballRect = GetRect();
        float overlapLeft = ballRect.left + ballRect.width - brickRect.left;
        float overlapRight = brickRect.left + brickRect.width - ballRect.left;
        float overlapTop = ballRect.top + ballRect.height - brickRect.top;
        float overlapBottom = brickRect.top + brickRect.height - ballRect.top;

        bool fromLeft = overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom;
        bool fromRight = overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom;
        bool fromTop = overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom;
        bool fromBottom = overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop;

        if (fromLeft || fromRight) {
            Reflect({ fromLeft ? 1.0f : -1.0f, 0.0f });
        }
        else {
            Reflect({ 0.0f, fromTop ? 1.0f : -1.0f });
        }
    }

    void Ball::Reflect(const sf::Vector2f& normal)
    {
      
        float dot = direction.x * normal.x + direction.y * normal.y;
        direction.x -= 2.0f * dot * normal.x;
        direction.y -= 2.0f * dot * normal.y;

        NormalizeDirection();
    }

    void Ball::NormalizeDirection()
    {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction.x /= length;
            direction.y /= length;
        }
    }

    void Ball::SetPosition(const sf::Vector2f& position)
    {
        sprite.setPosition(position);
    }
    void Ball::Draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
}