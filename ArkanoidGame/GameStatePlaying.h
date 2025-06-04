#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		GameStatePlayingData(const GameStatePlayingData&) = delete;
		GameStatePlayingData& operator=(const GameStatePlayingData&) = delete;

		GameStatePlayingData(GameStatePlayingData&&) = default;
		GameStatePlayingData& operator=(GameStatePlayingData&&) = default;

		GameStatePlayingData() = default;

		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);


	private:
		void CreateBricks();
		// Resources
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		Platform platform;
		Ball ball;
		std::vector<std::unique_ptr<Brick>> bricks;
		int score = 0;
		bool gameOverTriggered = false;
		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound gameOverSound;
	};
}
