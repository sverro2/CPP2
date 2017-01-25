#pragma once
#include "GameCharacterState.h"

class GameCharacterArchitectState : public GameCharacterState
{
public:
	GameCharacterArchitectState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

