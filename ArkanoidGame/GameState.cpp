#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "GameStateVictory.h"
#include <cassert>

namespace ArkanoidGame
{
    GameState::GameState(GameStateType type, bool isExclusivelyVisible)
        : type(type), isExclusivelyVisible(isExclusivelyVisible)
    {
        switch (type)
        {
        case GameStateType::MainMenu:
            data = new GameStateMainMenuData();
            static_cast<GameStateMainMenuData*>(data)->Init();
            break;
        case GameStateType::Playing:
            data = new GameStatePlayingData();
            static_cast<GameStatePlayingData*>(data)->Init();
            break;
        case GameStateType::GameOver:
            data = new GameStateGameOverData();
            static_cast<GameStateGameOverData*>(data)->Init();
            break;
        case GameStateType::ExitDialog:
            data = new GameStatePauseMenuData();
            static_cast<GameStatePauseMenuData*>(data)->Init();
            break;
        case GameStateType::Records:
            data = new GameStateRecordsData();
            static_cast<GameStateRecordsData*>(data)->Init();
            break;
        case GameStateType::Victory:
            data = new GameStateVictoryData();
            static_cast<GameStateVictoryData*>(data)->Init(0);
            break;
        default:
            assert(false);
            break;
        }
    }

    GameState::~GameState()
    {
        Cleanup();
    }

    GameState::GameState(GameState&& other) noexcept
        : type(other.type),
        data(other.data),
        isExclusivelyVisible(other.isExclusivelyVisible)
    {
        other.type = GameStateType::None;
        other.data = nullptr;
        other.isExclusivelyVisible = false;
    }

    GameState& GameState::operator=(GameState&& other) noexcept
    {
        if (this != &other)
        {
            Cleanup();

            type = other.type;
            data = other.data;
            isExclusivelyVisible = other.isExclusivelyVisible;

            other.type = GameStateType::None;
            other.data = nullptr;
            other.isExclusivelyVisible = false;
        }
        return *this;
    }

    void GameState::Cleanup() noexcept
    {
        if (data)
        {
            switch (type)
            {
            case GameStateType::MainMenu:
                delete static_cast<GameStateMainMenuData*>(data);
                break;
            case GameStateType::Playing:
                delete static_cast<GameStatePlayingData*>(data);
                break;
            case GameStateType::GameOver:
                delete static_cast<GameStateGameOverData*>(data);
                break;
            case GameStateType::ExitDialog:
                delete static_cast<GameStatePauseMenuData*>(data);
                break;
            case GameStateType::Records:
                delete static_cast<GameStateRecordsData*>(data);
                break;
            case GameStateType::Victory:
                delete static_cast<GameStateVictoryData*>(data);
                break;
            default:
                break;
            }
            data = nullptr;
        }
        type = GameStateType::None;
    }

    void GameState::Update(float timeDelta)
    {
        if (!data) return;

        switch (type)
        {
        case GameStateType::MainMenu:
            static_cast<GameStateMainMenuData*>(data)->Update(timeDelta);
            break;
        case GameStateType::Playing:
            static_cast<GameStatePlayingData*>(data)->Update(timeDelta);
            break;
        case GameStateType::GameOver:
            static_cast<GameStateGameOverData*>(data)->Update(timeDelta);
            break;
        case GameStateType::ExitDialog:
            static_cast<GameStatePauseMenuData*>(data)->Update(timeDelta);
            break;
        case GameStateType::Records:
            static_cast<GameStateRecordsData*>(data)->Update(timeDelta);
            break;
        case GameStateType::Victory:
            static_cast<GameStateVictoryData*>(data)->Update(timeDelta);
            break;
        default:
            assert(false);
            break;
        }
    }

    void GameState::Draw(sf::RenderWindow& window)
    {
        if (!data) return;

        switch (type)
        {
        case GameStateType::MainMenu:
            static_cast<GameStateMainMenuData*>(data)->Draw(window);
            break;
        case GameStateType::Playing:
            static_cast<GameStatePlayingData*>(data)->Draw(window);
            break;
        case GameStateType::GameOver:
            static_cast<GameStateGameOverData*>(data)->Draw(window);
            break;
        case GameStateType::ExitDialog:
            static_cast<GameStatePauseMenuData*>(data)->Draw(window);
            break;
        case GameStateType::Records:
            static_cast<GameStateRecordsData*>(data)->Draw(window);
            break;
        case GameStateType::Victory:
            static_cast<GameStateVictoryData*>(data)->Draw(window);
            break;
        default:
            assert(false);
            break;
        }
    }

    void GameState::HandleWindowEvent(sf::Event& event)
    {
        if (!data) return;

        switch (type)
        {
        case GameStateType::MainMenu:
            static_cast<GameStateMainMenuData*>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::Playing:
            static_cast<GameStatePlayingData*>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::GameOver:
            static_cast<GameStateGameOverData*>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::ExitDialog:
            static_cast<GameStatePauseMenuData*>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::Records:
            static_cast<GameStateRecordsData*>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::Victory:
            static_cast<GameStateVictoryData*>(data)->HandleWindowEvent(event);
            break;
        default:
            assert(false);
            break;
        }
    }

    void* GameState::GetData() const
    {
        return data;
    }
}