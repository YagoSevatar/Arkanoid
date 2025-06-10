#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "FireBallBonus.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "DurableBrick.h"
#include "SimpleBrick.h"
#include "PlatformShrinkBonus.h"
#include "PlatformExpandBonus.h"
#include "ExtraLifeBonus.h"
#include "cassert"

namespace ArkanoidGame
{
    void GameStatePlayingData::Init()
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Инициализация фона
        background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setFillColor(sf::Color::Black);

        // Инициализация текста
        assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setString("Score: 0");

        livesText.setFont(font);
        livesText.setCharacterSize(24);
        livesText.setFillColor(sf::Color::Green);
        livesText.setString("Lives: 3");
        livesText.setPosition(10.f, 20.f);

        inputHintText.setFont(font);
        inputHintText.setCharacterSize(24);
        inputHintText.setFillColor(sf::Color::White);
        inputHintText.setString("Use arrow keys to move, ESC to pause");
        inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));
        inputHintText.setPosition(SCREEN_WIDTH - 10.f, 10.f);

        // Инициализация игровых объектов
        platform.Init();
        ball.Init();
        CreateBricks();
    }

    void GameStatePlayingData::CreateBricks()
    {
        bricks.clear();
        const int rows = 5;
        const int cols = 10;
        const float brickWidth = SCREEN_WIDTH / cols;
        const float brickHeight = 30.f;

        for (int row = 0; row < rows; ++row)
        {
            std::vector<sf::Color> durableColors;
            switch (row % 5)
            {
            case 0: durableColors = { sf::Color(200,200,255), sf::Color(150,150,255), sf::Color(100,100,255) }; break;
            case 1: durableColors = { sf::Color(255,200,200), sf::Color(255,150,150), sf::Color(255,100,100) }; break;
            case 2: durableColors = { sf::Color(200,255,200), sf::Color(150,255,150), sf::Color(100,255,100) }; break;
            case 3: durableColors = { sf::Color(255,255,200), sf::Color(255,255,150), sf::Color(255,255,100) }; break;
            default: durableColors = { sf::Color(255,200,255), sf::Color(255,150,255), sf::Color(255,100,255) };
            }

            for (int col = 0; col < cols; ++col)
            {
                sf::Vector2f position(col * brickWidth, row * brickHeight + 50.f);
                sf::Vector2f size(brickWidth - 2.f, brickHeight - 2.f);

                if (col % 3 == 0)
                {
                    bricks.emplace_back(std::make_unique<DurableBrick>(position, size, durableColors));
                }
                else
                {
                    bricks.emplace_back(std::make_unique<SimpleBrick>(position, size, durableColors.back()));
                }
            }
        }
    }

    void GameStatePlayingData::SpawnBonus(const sf::Vector2f& position)
    {
        if (rand() % 100 < 25) // 25% шанс выпадения бонуса
        {
            Bonus::Type type = static_cast<Bonus::Type>(rand() % static_cast<int>(Bonus::Type::Count));

            std::unique_ptr<Bonus> bonus;
            switch (type)
            {
            case Bonus::Type::FireBall:
                bonus = std::make_unique<FireBallBonus>(position, ball);
                break;
            case Bonus::Type::PlatformExpand:
                bonus = std::make_unique<PlatformExpandBonus>(position, platform);
                break;
            case Bonus::Type::PlatformShrink:
                bonus = std::make_unique<PlatformShrinkBonus>(position, platform);
                break;
            case Bonus::Type::ExtraLife:
                bonus = std::make_unique<ExtraLifeBonus>(position);
                break;
            }

            if (bonus)
            {
                bonus->GetShape().setFillColor(Bonus::GetColorForType(type));
                activeBonuses.push_back(std::move(bonus));
            }
        }
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

    void GameStatePlayingData::Update(float deltaTime)
    {
        platform.Update(deltaTime);
        ball.Update(deltaTime);
        ball.HandleBoundaryCollisions();

        // Столкновение с платформой
        if (platform.CheckCollisionWithBall(ball))
        {
            ball.ReboundFromPlatform(platform.GetPosition(), platform.GetRect().width);
            sf::Vector2f ballPos = ball.GetPosition();
            ballPos.y = platform.GetRect().top - BALL_SIZE / 2.0f;
            ball.SetPosition(ballPos);
        }

        // Столкновение с блоками
        for (auto it = bricks.begin(); it != bricks.end(); )
        {
            Brick* brick = it->get();
            if (!brick->IsDestroyed() && ball.GetRect().intersects(brick->GetBounds()))
            {
                bool isDurable = dynamic_cast<DurableBrick*>(brick) != nullptr;

                if (ball.IsPiercing())
                {
                    if (brick->OnHit())
                    {
                        score += isDurable ? 3 : 1;
                        SpawnBonus(brick->GetPosition());
                        it = bricks.erase(it);
                        continue;
                    }
                }
                else
                {
                    if (brick->OnHit())
                    {
                        score += isDurable ? 3 : 1;
                        SpawnBonus(brick->GetPosition());
                        it = bricks.erase(it);
                    }
                    ball.ReboundFromBrick(brick->GetBounds());
                    break;
                }
            }
            ++it;
        }

        // Обновление бонусов
        for (auto it = activeBonuses.begin(); it != activeBonuses.end(); )
        {
            (*it)->Update(deltaTime);

            if ((*it)->CheckCollision(platform))
            {
                (*it)->Apply();
                appliedBonuses.push_back(std::move(*it));
                it = activeBonuses.erase(it);
            }
            else if ((*it)->GetPosition().y > SCREEN_HEIGHT || (*it)->ShouldRemove())
            {
                it = activeBonuses.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Удаление завершенных бонусов
        for (auto it = appliedBonuses.begin(); it != appliedBonuses.end(); )
        {
            if ((*it)->ShouldRemove())
            {
                (*it)->Remove();
                it = appliedBonuses.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Проверка завершения уровня
        if (bricks.empty() && !Application::Instance().GetGame().IsGameCompleted())
        {
            Game& game = Application::Instance().GetGame();
            game.SetGameCompleted(true);
            game.UpdateRecord(PLAYER_NAME, score);
            game.PushState(GameStateType::Victory, true);
        }

        // Проверка проигрыша
        if (ball.GetPosition().y + BALL_SIZE / 2.f > SCREEN_HEIGHT)
        {
            Application::Instance().GetGame().LoseLife();
            lives = Application::Instance().GetGame().GetLives();
            livesText.setString("Lives: " + std::to_string(lives));

            if (lives > 0)
            {
                // Рестарт уровня
                ball.Init();
                platform.Init();

                // Деактивация всех бонусов
                for (auto& bonus : appliedBonuses)
                {
                    bonus->Remove();
                }
                appliedBonuses.clear();
                activeBonuses.clear();
            }
            else
            {
                // Конец игры
                Application::Instance().GetGame().ResetLives();
                Application::Instance().GetGame().PushState(GameStateType::GameOver, false);
            }
        }

        // Обновление счета
        scoreText.setString("Score: " + std::to_string(score));
    }

    void GameStatePlayingData::Draw(sf::RenderWindow& window)
    {
        window.draw(background);

        for (const auto& brick : bricks)
        {
            brick->Draw(window);
        }

        for (const auto& bonus : activeBonuses)
        {
            bonus->Draw(window);
        }

        platform.Draw(window);
        ball.Draw(window);
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(inputHintText);
    }
}