#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "SimpleBrick.h"
#include "DurableBrick.h"
#include <algorithm>

namespace ArkanoidGame
{
    void GameStatePlayingData::Init()
    {
        // Init resources
        assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
        assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

        // Init game objects
        background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setFillColor(sf::Color::Black);

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
        CreateBricks();
        gameOverSound.setBuffer(gameOverSoundBuffer);
    }

    void GameStatePlayingData::CreateBricks()
    {
        const int rows = 5;
        const int cols = 10;
        const float brickWidth = SCREEN_WIDTH / cols;
        const float brickHeight = 30.f;

        for (int row = 0; row < rows; ++row)
        {

            std::vector<sf::Color> durableColors;
            switch (row % 5)
            {
            case 0:
                durableColors = { sf::Color(200,200,255), sf::Color(150,150,255), sf::Color(100,100,255) };
                break;
            case 1:
                durableColors = { sf::Color(255,200,200), sf::Color(255,150,150), sf::Color(255,100,100) };
                break;
            case 2:
                durableColors = { sf::Color(200,255,200), sf::Color(150,255,150), sf::Color(100,255,100) };
                break;
            case 3:
                durableColors = { sf::Color(255,255,200), sf::Color(255,255,150), sf::Color(255,255,100) };
                break;
            default:
                durableColors = { sf::Color(255,200,255), sf::Color(255,150,255), sf::Color(255,100,255) };
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
                    bricks.emplace_back(std::make_unique<SimpleBrick>(
                        position, size, durableColors.back()));
                }
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

    void GameStatePlayingData::Update(float timeDelta)
    {
        platform.Update(timeDelta);
        ball.Update(timeDelta);
        ball.HandleBoundaryCollisions();
        if (platform.CheckCollisionWithBall(ball))
        {
            ball.ReboundFromPlatform(platform.GetPosition(), platform.GetRect().width);
            sf::Vector2f ballPos = ball.GetPosition();
            ballPos.y = platform.GetRect().top - BALL_SIZE / 2.0f;
            ball.SetPosition(ballPos);
        }

        for (auto it = bricks.begin(); it != bricks.end(); )
        {
            Brick* brick = it->get();
            if (!brick->IsDestroyed() && ball.GetRect().intersects(brick->GetBounds()))
            {
                DurableBrick* durableBrick = dynamic_cast<DurableBrick*>(brick);
                if (durableBrick)
                {
                    if (durableBrick->OnHit())
                    {
                        score += 3;
                        
                    }
               
                }
                else
                {
                    if (brick->OnHit())
                    {
                        score += 1;
             
                    }
                }

                ball.ReboundFromBrick(brick->GetBounds());
                break;
            }
            ++it;
        }

        bricks.erase(
            std::remove_if(bricks.begin(), bricks.end(),
                [](const std::unique_ptr<Brick>& brick) {
                    return brick->IsDestroyed();
                }),
            bricks.end()
        );

        if (bricks.empty() && !Application::Instance().GetGame().IsGameCompleted())
        {
            Game& game = Application::Instance().GetGame();
            game.SetGameCompleted(true);
            game.UpdateRecord(PLAYER_NAME, score);
            game.PushState(GameStateType::Victory, true);
        }

        const float ballBottom = ball.GetPosition().y + BALL_SIZE / 2.f;
        if (ballBottom > SCREEN_HEIGHT)
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
            brick->Draw(window);
        }

        platform.Draw(window);
        ball.Draw(window);
        window.draw(scoreText);
        window.draw(inputHintText);
    }
}