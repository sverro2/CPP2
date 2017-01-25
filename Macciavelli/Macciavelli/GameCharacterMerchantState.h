#pragma once
#include "GameCharacterState.h"

class GameCharacterMerchantState : public GameCharacterState
{
public:
	GameCharacterMerchantState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

