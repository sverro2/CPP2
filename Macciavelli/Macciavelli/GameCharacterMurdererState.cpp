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
}

