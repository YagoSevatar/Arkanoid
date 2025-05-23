#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		platform.Init();
		ball.Init();
		const int rows = 5;
		const int cols = 10;
		const float brickWidth = SCREEN_WIDTH / cols;
		const float brickHeight = 30.f;

		for (int row = 0; row < rows; ++row)
		{
			sf::Color color;
			switch (row % 5)
			{
			case 0: color = sf::Color::Red; break;
			case 1: color = sf::Color::Green; break;
			case 2: color = sf::Color::Blue; break;
			case 3: color = sf::Color::Yellow; break;
			default: color = sf::Color::Magenta; break;
			}

			for (int col = 0; col < cols; ++col)
			{
				bricks.emplace_back(
					sf::Vector2f(col * brickWidth, row * brickHeight + 50.f),
					sf::Vector2f(brickWidth - 2.f, brickHeight - 2.f),
					color
				);
			}
		}
	
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		platform.Update(timeDelta);
		ball.Update(timeDelta);

		sf::Vector2f ballPos = ball.GetPosition();
		if (ballPos.x <= BALL_SIZE / 2 || ballPos.x >= SCREEN_WIDTH - BALL_SIZE / 2) {
			ball.ReboundFromBrick(); 
		}
		if (ballPos.y <= BALL_SIZE / 2) {
			ball.ReboundFromBrick(); 
		}

		if (platform.CheckCollisionWithBall(ball) && ball.GetPosition().y < platform.GetRect().top)
		{
			ball.ReboundFromPlatform(
				platform.GetPosition(),
				platform.GetRect().width
			);
		}

		for (auto it = bricks.begin(); it != bricks.end(); )
		{
			if (!it->IsDestroyed() && ball.GetRect().intersects(it->GetBounds()))
			{
				it->Destroy();
				ball.ReboundFromBrick();
				score += 1;
				scoreText.setString("Score: " + std::to_string(score));
				break;
			}
			else
			{
				++it;
			}
		}
		bricks.erase(
			std::remove_if(bricks.begin(), bricks.end(),
				[](const Brick& brick) { return brick.IsDestroyed(); }),
			bricks.end()
		);
		if (bricks.empty())
		{
			gameOverSound.play();
			Game& game = Application::Instance().GetGame();
			game.UpdateRecord(PLAYER_NAME, score);
			game.PushState(GameStateType::GameOver, false);
		}

		if (ballPos.y > SCREEN_HEIGHT)
		{
			gameOverSound.play();
			Game& game = Application::Instance().GetGame();
			game.UpdateRecord(PLAYER_NAME, score);
			game.PushState(GameStateType::GameOver, false);
		}
	}
	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(background);

		for (const auto& brick : bricks)
		{
			brick.Draw(window);
		}

		platform.Draw(window);
		ball.Draw(window);
		window.draw(scoreText);
		window.draw(inputHintText);
	}
}