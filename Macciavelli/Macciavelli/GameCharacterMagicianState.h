#pragma once
#include "GameCharacterState.h"

class GameCharacterMagicianState : public GameCharacterState
{
	GameCharacterMagicianState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

