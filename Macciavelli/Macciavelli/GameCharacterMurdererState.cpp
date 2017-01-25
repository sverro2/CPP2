#include "GameCharacterMurdererState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterMurdererState::GameCharacterMurdererState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::MURDERER }
{
}

int GameCharacterMurdererState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterMurdererState::DoCharacterAction()
{
	std::vector<std::string> characters;

	for (const auto character : _context.LookAtCharacterDeck()) {
		characters.push_back(Character::CharacterEnumToString(character.GetCharacterType()));
	}

	int index{ _server.RequestOptionByIndex(_context.GetCurrentPlayer()->GetName(), characters, "What character would you like to kill?") };

	//set character robbed
	_context.SetKilledCharacter(std::move(std::make_unique<Character>(_context.LookAtCharacterDeck().at(index))));
}

