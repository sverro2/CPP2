#pragma once
#include "GameCharacterState.h"

	class GameCharacterKingState : public GameCharacterState
{
		GameCharacterKingState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

