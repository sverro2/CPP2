#pragma once

#include "GameCharacterState.h"

class GameCharacterCondottiereState : public GameCharacterState
{
public:
	GameCharacterCondottiereState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

