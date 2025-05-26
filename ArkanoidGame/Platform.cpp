#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	void Platform::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f });
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(-timeDelta * PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(timeDelta * PLATFORM_SPEED);
		}
	}

	void Platform::Move(float speed)
	{
		auto position = sprite.getPosition();
		position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}

	bool Platform::CheckCollisionWithBall(const Ball& ball) const
{
    sf::FloatRect platformRect = sprite.getGlobalBounds();
    sf::FloatRect ballRect = ball.GetRect();
    
    if (!platformRect.intersects(ballRect))
        return false;
  
    sf::Vector2f ballCenter = ball.GetPosition();
    float ballRadius = BALL_SIZE / 2.0f;
 
    if (ballCenter.y + ballRadius > platformRect.top && 
        ballCenter.y - ballRadius < platformRect.top &&
        ballCenter.x > platformRect.left && 
        ballCenter.x < platformRect.left + platformRect.width)
    {
        return true;
    }
    
    return false;
}
}