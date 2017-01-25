#pragma once
#include "GameCharacterState.h"

class GameCharacterThiefState : public GameCharacterState
{
	GameCharacterThiefState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

