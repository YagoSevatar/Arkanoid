#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanoidGame
{
    enum class GameStateType
    {
        None = 0,
        MainMenu,
        Playing,
        GameOver,
        ExitDialog,
        Records,
        Victory,
    };

    class GameState
    {
    public:
        GameState(GameStateType type, bool isExclusivelyVisible);
        ~GameState();
        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;
        GameState(GameState&& other) noexcept;
        GameState& operator=(GameState&& other) noexcept;

        GameStateType GetType() const { return type; }
        bool IsExclusivelyVisible() const { return isExclusivelyVisible; }

        void Update(float timeDelta);
        void Draw(sf::RenderWindow& window);
        void HandleWindowEvent(sf::Event& event);
        void* GetData() const;

    private:
        void Cleanup() noexcept;

        GameStateType type = GameStateType::None;
        void* data = nullptr;
        bool isExclusivelyVisible = false;
    };
}