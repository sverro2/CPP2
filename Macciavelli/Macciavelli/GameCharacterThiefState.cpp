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
}
