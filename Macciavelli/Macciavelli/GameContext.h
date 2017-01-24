#pragma once
#include <vector>
#include <memory>
#include <stack>
#include <vector>
#include <random>
#include "Player.h"
#include "GameState.h"
#include "Building.h"
#include "King.h"

class IServer;
class GameContext
{
public:
	GameContext(IServer& server);
	void SwitchToState(std::unique_ptr<GameState>&& _state);
	void ResetAll();
	void ResetRemainingCharacterCards();
	void ShuffleBuildingCards(std::vector<Building>&& all_remaining_buildings = std::vector<Building>());
	void AddCardToGarbagePile(Building building);
	void SetCurrentPlayer(const std::shared_ptr<Player>& player);
	void AddPlayer(const std::shared_ptr<Player>& player);
	void SetCharacterDeck(std::vector<Character>&& character_deck);

	//getters
	const std::vector<std::shared_ptr<Player>>& GetPlayers() const;
	const Building TakeBuildingCard();
	const std::vector<Character>& LookAtRemainingCharacterCards();
	const bool TakeCharacterCard(Character character);
	const bool HasBuildingCards();
	const std::shared_ptr<Player>& GetPlayerAtRightHandOfCurrent() const;
	const std::shared_ptr<Player>& GetCurrentPlayer() const;
	const std::default_random_engine& GetRandomEngine() const;
	std::unique_ptr<King>& GetKingReference();
private:
	IServer& _server;
	std::vector<shared_ptr<Player>> _players;
	std::shared_ptr<Player> _current_player;

	//character
	std::vector<Character> _character_deck;
	std::vector<Character> _characters_remaining;

	//buildings
	std::stack<Building> _building_deck;
	std::stack<Building> _garbage_pile;

	void InitGame();
	std::unique_ptr<GameState> _current_gamestate;
	std::unique_ptr<King> _king;
	std::default_random_engine _random_engine;
};

