#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>
#include <memory>
#include "FireBallBonus.h"
#include "Bonus.h"
#include "GameState.h"
#include <string>

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
		sf::RectangleShape background;
		Platform platform;
		Ball ball;
		std::vector<std::unique_ptr<Brick>> bricks;
		std::vector<std::unique_ptr<Bonus>> activeBonuses;
		std::vector<std::unique_ptr<Bonus>> appliedBonuses;
		sf::Text scoreText;
		sf::Text inputHintText;
		std::string currentLevel;
		int score = 0;
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void SpawnBonus(const sf::Vector2f& position);
		void UpdateLivesDisplay();
	private:
		void CreateBricks();
		void CheckBonusCollisions();
		void UpdateBonuses(float deltaTime);
		// Resources
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		int lives = 3;
		sf::Text livesText;
		// Game data
		bool gameOverTriggered = false;
		// Sounds
		sf::Sound gameOverSound;
	};
}
