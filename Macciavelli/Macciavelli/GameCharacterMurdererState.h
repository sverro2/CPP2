#pragma once
#include "GameCharacterState.h"

class GameCharacterMurdererState : public GameCharacterState
{
	GameCharacterMurdererState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};