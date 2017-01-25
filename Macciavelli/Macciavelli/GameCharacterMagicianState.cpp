#include "GameCharacterMagicianState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterMagicianState::GameCharacterMagicianState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::MAGICIAN }
{
}

int GameCharacterMagicianState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterMagicianState::DoCharacterAction()
{
}
