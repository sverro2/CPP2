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

	//getters
	const Building TakeBuildingCard();
	const std::vector<Character>& LookAtRemainingCharacterCards();
	const bool TakeCharacterCard(Character character);

	const std::default_random_engine& GetRandomEngine() const;
private:
	IServer& _server;
	std::vector<Player> _players;
	std::string _current_player;

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

