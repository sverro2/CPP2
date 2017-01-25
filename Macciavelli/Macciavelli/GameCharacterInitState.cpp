#include <memory>
#include "GameCharacterInitState.h"
#include "GameContext.h"


void GameCharacterInitState::EnterState()
{
	//Clear player characters.
	_context.ClearPlayerCharacters();

	//Clear player state
	_context.SetRobbedCharacter(nullptr);
	_context.SetKilledCharacter(nullptr);

	//current king is current player
	_context.SetCurrentPlayer(_context.GetKingReference()->GetKing());

	//reset all cards
	_context.ResetRemainingCharacterCards();

	//reset current character index
	_context.ResetCurrentCharacterIndex();


	for (int i = 1; i <= 4; i++)
	{
		//Get current player.
		std::shared_ptr<Player> current_player = _context.GetCurrentPlayer();

		//Available characters.
		auto available_characters = _context.LookAtRemainingCharacterCards();

		//Available character names.
		std::vector<std::string> available_character_names;

		//Setting the available character names.
		for (int j = 0; j < available_characters.size(); j++)
		{
			available_character_names.push_back(available_characters[j].GetCharacterName());
		}

		int character_index = _server.RequestOptionByIndex(current_player->GetName(), available_character_names, "What character do you choose to be?");

		//Remove character card from deck.
		_context.TakeCharacterCard(available_characters[character_index]);

		//Assign character to player.
		_context.AssignCharacterToPlayer(available_characters.at(character_index).GetCharacterType(), current_player);

		//Remove character from temp values.
		available_characters = _context.LookAtRemainingCharacterCards();
		available_character_names.erase(available_character_names.begin() + character_index);

		character_index = _server.RequestOptionByIndex(current_player->GetName(), available_character_names, "What character do you want to get rid of?");

		//Remove character card from deck.
		_context.TakeCharacterCard(available_characters[character_index]);

		//Set next player.
		_context.SetCurrentPlayer(_context.GetPlayerAtRightHandOfCurrent());
	}

	//Initialise base building cards for eacht player.
	for (int i = 0; i < _context.GetPlayers().size(); i++)
	{
		//For each player take 4 building cards.
		for (int j = 1; j <= 4; j++)
		{
			_context.GetPlayers()[i]->AddBuilding(_context.TakeBuildingCard());
		}
	}

	_context.SwitchToNextCharacter();
}

void GameCharacterInitState::LeaveState()
{
}
