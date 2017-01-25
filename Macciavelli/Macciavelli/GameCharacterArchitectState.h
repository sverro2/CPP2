#pragma once
#include "GameCharacterState.h"

class GameCharacterArchitectState : public GameCharacterState
{
	GameCharacterArchitectState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

