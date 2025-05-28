#include "GameStateVictory.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>

namespace ArkanoidGame
{
    void GameStateVictoryData::Init(int score)
    {
        assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

        finalScore = score;

        sf::Color backgroundColor = sf::Color::Black;
        backgroundColor.a = 200;
        background.setFillColor(backgroundColor);

        victoryText.setFont(font);
        victoryText.setCharacterSize(48);
        victoryText.setStyle(sf::Text::Bold);
        victoryText.setFillColor(sf::Color::Green);
        victoryText.setString("VICTORY!");

        scoreText.setFont(font);
        scoreText.setCharacterSize(36);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setString("Your score: " + std::to_string(finalScore));

        hintText.setFont(font);
        hintText.setCharacterSize(24);
        hintText.setFillColor(sf::Color::White);
        hintText.setString("Press Y to restart\nN to main menu");
    }

    void GameStateVictoryData::HandleWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            Game& game = Application::Instance().GetGame();

            if (event.key.code == sf::Keyboard::Y)
            {
                game.SwitchStateTo(GameStateType::Playing);
            }
            else if (event.key.code == sf::Keyboard::N)
            {
                game.SwitchStateTo(GameStateType::MainMenu);
            }
        }
    }

    void GameStateVictoryData::Update(float timeDelta)
    {
   
    }

    void GameStateVictoryData::Draw(sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = window.getView().getSize();

        background.setSize(viewSize);
        window.draw(background);

        victoryText.setOrigin(GetTextOrigin(victoryText, { 0.5f, 0.5f }));
        victoryText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
        window.draw(victoryText);

        scoreText.setOrigin(GetTextOrigin(scoreText, { 0.5f, 0.5f }));
        scoreText.setPosition(viewSize.x / 2.f, viewSize.y / 2 + 20.f);
        window.draw(scoreText);

        hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 0.5f }));
        hintText.setPosition(viewSize.x / 2.f, viewSize.y / 2 + 100.f);
        window.draw(hintText);
    }
}