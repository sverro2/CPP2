#pragma once
#include "GameCharacterState.h"

class GameCharacterMerchantState : public GameCharacterState
{
	GameCharacterMerchantState(GameContext& context, IServer& server);

	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

