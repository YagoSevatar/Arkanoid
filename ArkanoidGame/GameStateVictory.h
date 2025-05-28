#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    class GameStateVictoryData
    {
    public:
        void Init(int score);
        void HandleWindowEvent(const sf::Event& event);
        void Update(float timeDelta);
        void Draw(sf::RenderWindow& window);
  
    private:
        sf::Font font;
        sf::Text victoryText;
        sf::Text scoreText;
        sf::Text hintText;
        sf::RectangleShape background;
        int finalScore;
    };
}