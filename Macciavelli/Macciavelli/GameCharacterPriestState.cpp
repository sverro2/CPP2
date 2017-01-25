#include "GameCharacterPriestState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterPriestState::GameCharacterPriestState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::PRIEST }
{
}

int GameCharacterPriestState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterPriestState::DoCharacterAction()
{
}
