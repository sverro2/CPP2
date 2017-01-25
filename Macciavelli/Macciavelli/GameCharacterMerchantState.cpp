#include "GameCharacterMerchantState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterMerchantState::GameCharacterMerchantState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::MERCHANT }
{
}

int GameCharacterMerchantState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterMerchantState::DoCharacterAction()
{
}
