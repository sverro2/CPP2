#include "GameCharacterKingState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterKingState::GameCharacterKingState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::KING }
{
}

int GameCharacterKingState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterKingState::DoCharacterAction()
{
}
