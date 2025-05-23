#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);

		void ReboundFromPlatform(const sf::Vector2f& platformPosition, float platformWidth);
		void ReboundFromBrick();
	private:
		sf::Vector2f direction;
	};
}


