#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>
#include "Platform.h"
namespace
{
	// id textures
	const std::string TEXTURE_ID = "ball";
}

namespace ArkanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f });

		const float angle = 45.f + rand() % 90; // [45, 135] degree
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x <= 0 || pos.x >= SCREEN_WIDTH) {
			direction.x *= -1;
		}

		if (pos.y <= 0 || pos.y >= SCREEN_HEIGHT) {
			direction.y *= -1;
		}
	}

	void Ball::ReboundFromPlatform(const sf::Vector2f& platformPosition, float platformWidth)
	{
		float hitPosition = (GetPosition().x - platformPosition.x) / (platformWidth / 2.0f);
		direction.x = hitPosition * 0.5f; 
		direction.y = -fabs(direction.y); 

		float length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;
	}
	void Ball::ReboundFromBrick()
	{
		direction.y *= -1; 
	}
}