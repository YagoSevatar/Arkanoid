#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "GameSettings.h"
#include "GameState.h"
#include <unordered_map>
#include "ScoreManager.h"

namespace ArkanoidGame
{
	enum class GameOptions : std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();
		int GetLives() const { return lives; }
		void LoseLife() { lives--; }
		void AddLife() { lives++; }
		void ResetLives() { lives = 3; }
		ScoreManager& GetScoreManager() { return scoreManager; }
		int GetCurrentScore() const { return scoreManager.GetCurrentScore(); }
		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void Shutdown();
		GameState& GetCurrentState();
		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);
		bool IsGameCompleted() const { return isGameCompleted; }
		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);
		void SetGameCompleted(bool completed) { isGameCompleted = completed; }
		// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopState();

		// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);


	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
		bool isGameCompleted = false;
		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;
		ScoreManager scoreManager;
		int lives = 3;
	};
}
