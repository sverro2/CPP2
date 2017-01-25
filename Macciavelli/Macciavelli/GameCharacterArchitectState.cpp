#include "GameCharacterArchitectState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterArchitectState::GameCharacterArchitectState(GameContext & context, IServer & server) : GameCharacterState{context, server, CharacterType::ARCHITECT}
{
}

int GameCharacterArchitectState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterArchitectState::DoCharacterAction()
{
}
