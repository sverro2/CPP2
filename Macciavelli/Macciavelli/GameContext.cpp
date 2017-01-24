#include <algorithm>
#include "GameContext.h"
#include "IServer.h"
#include "GameInitState.h"

GameContext::GameContext(IServer& server) : _server{ server }
{
	//Player roles in good order.
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(MURDERER, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(THIEF, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(MAGICIAN, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(KING, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(PRIEST, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(MERCHANT, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(ARCHITECT, nullptr));
	_player_roles.insert(std::pair<CharacterType, std::shared_ptr<Player>>(CONDONTIERE, nullptr));

	//Initialises game.
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

const std::vector<std::shared_ptr<Player>>& GameContext::GetPlayers() const
{
	return _players;
}

void GameContext::ResetAll()
{
	_current_player = nullptr;
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

void GameContext::AssignCharacterToPlayer(const CharacterType character, const std::shared_ptr<Player> player)
{
	_player_roles[character] = player;
}

void GameContext::ClearPlayerCharacters()
{
	_player_roles[MURDERER] = nullptr;
	_player_roles[THIEF] = nullptr;
	_player_roles[MAGICIAN] = nullptr;
	_player_roles[KING] = nullptr;
	_player_roles[PRIEST] = nullptr;
	_player_roles[MERCHANT] = nullptr;
	_player_roles[ARCHITECT] = nullptr;
	_player_roles[CONDONTIERE] = nullptr;
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

const std::shared_ptr<Player>& GameContext::GetPlayerAtRightHandOfCurrent() const
{
	auto current_player_index{ std::find(_players.begin(), _players.end(), _current_player) };
	
	current_player_index++;

	if (current_player_index == _players.end()) {
		return _players[0];
	}
	else {
		return *current_player_index;
	}
}

void GameContext::SetCurrentPlayer(const std::shared_ptr<Player>& player)
{
	_current_player = player;
}

void GameContext::AddPlayer(const std::shared_ptr<Player>& player)
{
	_players.push_back(player);
}

void GameContext::SetCharacterDeck(std::vector<Character>&& character_deck)
{
	_character_deck = character_deck;
}

const std::shared_ptr<Player>& GameContext::GetCurrentPlayer() const
{
	return _current_player;
}

const std::default_random_engine & GameContext::GetRandomEngine() const
{
	return _random_engine;
}

std::unique_ptr<King>& GameContext::GetKingReference()
{
	return _king;
}

void GameContext::InitGame()
{
	SwitchToState(std::move(std::make_unique<GameInitState>(*this, _server)));
}
