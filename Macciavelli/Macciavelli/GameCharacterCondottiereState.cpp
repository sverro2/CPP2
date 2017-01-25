#include "GameCharacterCondottiereState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterCondottiereState::GameCharacterCondottiereState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::CONDONTIERE }
{
}

int GameCharacterCondottiereState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterCondottiereState::DoCharacterAction()
{
}