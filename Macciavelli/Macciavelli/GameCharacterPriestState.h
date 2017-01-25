#pragma once
#include "GameCharacterState.h"

class GameCharacterPriestState : public GameCharacterState
{
	GameCharacterPriestState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};
