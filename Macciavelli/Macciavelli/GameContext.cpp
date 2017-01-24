#include <algorithm>
#include "GameContext.h"
#include "IServer.h"
#include "GameInitState.h"

GameContext::GameContext(IServer& server) : _server{ server }
{
	InitGame();
}

void GameContext::SwitchToState(std::unique_ptr<GameState>&& state)
{
	//Notify old state to start the "LeaveState"
	if (_current_gamestate != nullptr) {
		_current_gamestate->LeaveState();
	}

	//Set new state
	_current_gamestate = std::move(state);

	//Start new state
	_current_gamestate->EnterState();
}

const std::vector<Player> GameContext::GetPlayers() const
{
	return _players;
}

void GameContext::ResetAll()
{
	_current_player = "";
	_players.clear();
	_character_deck.clear();
	_building_deck.swap(std::stack<Building>());
	_garbage_pile.swap(std::stack<Building>());
}

void GameContext::ResetRemainingCharacterCards()
{
	_characters_remaining = _character_deck;
}

void GameContext::ShuffleBuildingCards(std::vector<Building>&& all_remaining_buildings)
{
	if (all_remaining_buildings.empty()) {
		//all buildings on the deck
		while (!_building_deck.empty()) {
			all_remaining_buildings.push_back(_building_deck.top());
			_building_deck.pop();
		}

		//all buildings in the garbage pile
		while (!_garbage_pile.empty()) {
			all_remaining_buildings.push_back(_garbage_pile.top());
			_garbage_pile.pop();
		}
	}
	else {
		//make sure all stacks are empty
		while (!_building_deck.empty()) {
			_building_deck.pop();
		}
		while (!_garbage_pile.empty()) {
			_garbage_pile.pop();
		}
	}

	std::shuffle(all_remaining_buildings.begin(), all_remaining_buildings.end(), _random_engine);

	for (auto& building : all_remaining_buildings) {
		_building_deck.push(building);
	}
}

void GameContext::AddCardToGarbagePile(Building building)
{
	_building_deck.push(building);
}

const Building GameContext::TakeBuildingCard()
{
	Building building{ _building_deck.top() };
	_building_deck.pop();
	return building;
}

const std::vector<Character>& GameContext::LookAtRemainingCharacterCards()
{
	return _characters_remaining;
}

const bool GameContext::TakeCharacterCard(Character character)
{
	auto character_iterator{ std::find(_characters_remaining.begin(), _characters_remaining.end(), character) };

	if (character_iterator != _characters_remaining.end()) {
		return false;
	}
	else {
		_characters_remaining.erase(character_iterator);
		return true;
	}
}

const bool GameContext::HasBuildingCards()
{
	return !_building_deck.empty();
}

const std::default_random_engine & GameContext::GetRandomEngine() const
{
	return _random_engine;
}

void GameContext::InitGame()
{
	SwitchToState(std::move(std::make_unique<GameInitState>(*this, _server)));
}
