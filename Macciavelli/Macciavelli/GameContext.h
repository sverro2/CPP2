#pragma once
#include <map>
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
	void SwitchToNextCharacter();
	void ResetAll();
	void ResetRemainingCharacterCards();
	void ShuffleBuildingCards(std::vector<Building>&& all_remaining_buildings = std::vector<Building>());
	void AddCardToGarbagePile(Building building);
	void AssignCharacterToPlayer(const CharacterType character, const std::shared_ptr<Player> player);
	void ClearPlayerCharacters();
	void SetCurrentPlayer(const std::shared_ptr<Player>& player);
	void AddPlayer(const std::shared_ptr<Player>& player);
	void SetCharacterDeck(std::vector<Character>&& character_deck);

	//Make sure the right character gets activated.
	const size_t GetCurrentCharacterIndex() const;
	void ResetCurrentCharacterIndex();
	const size_t GetAmountOfCharactersInGame() const;

	//setters
	void SetRobbedCharacter(std::unique_ptr<Character>&& robbed_character);
	void SetKilledCharacter(std::unique_ptr<Character>&& killed_character);

	//Mark game as done
	void MarkGameAsDone();

	//Getters
	const std::vector<std::shared_ptr<Player>>& GetPlayers() const;
	const Building TakeBuildingCard();
	const std::vector<Character>& LookAtRemainingCharacterCards();
	const bool TakeCharacterCard(Character character);
	const bool HasBuildingCards();
	const std::shared_ptr<Player>& GetPlayerAtRightHandOfCurrent() const;
	const std::shared_ptr<Player>& GetCurrentPlayer() const;
	const std::default_random_engine& GetRandomEngine() const;
	std::unique_ptr<King>& GetKingReference();
	const std::map<CharacterType, std::shared_ptr<Player>>& GetPlayerRoles() const;
	const std::vector<Character>& LookAtCharacterDeck();

	const std::unique_ptr<Character>& GetRobbedCharacter() const;
	const std::unique_ptr<Character>& GetKilledCharacter() const;
private:
	IServer& _server;
	std::vector<shared_ptr<Player>> _players;
	std::shared_ptr<Player> _current_player;

	//Character.
	std::vector<Character> _character_deck;
	std::vector<Character> _characters_remaining;

	//Player roles.
	std::map<CharacterType, std::shared_ptr<Player>> _player_roles;

	//Buildings.
	std::stack<Building> _building_deck;
	std::stack<Building> _garbage_pile;

	void InitGame();
	std::unique_ptr<GameState> _current_gamestate;
	std::unique_ptr<King> _king;
	std::default_random_engine _random_engine;

	//The character index that is activated right now.
	size_t _character_index;

	//character states
	std::unique_ptr<Character> _killed_character;
	std::unique_ptr<Character> _robbed_character;

	//End of game
	bool _done;
};

