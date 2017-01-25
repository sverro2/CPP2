#include "GameCharacterThiefState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterThiefState::GameCharacterThiefState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::THIEF }
{
}

int GameCharacterThiefState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterThiefState::DoCharacterAction()
{
	std::vector<std::string> characters;

	for (const auto character : _context.LookAtCharacterDeck()) {
		characters.push_back(Character::CharacterEnumToString(character.GetCharacterType()));
	}

	int index{ _server.RequestOptionByIndex(_context.GetCurrentPlayer()->GetName(), characters, "What character would you like to rob?") };

	//set character robbed
	_context.SetRobbedCharacter(std::move(std::make_unique<Character>(_context.LookAtCharacterDeck().at(index))));
}
