#pragma once
#include "GameCharacterState.h"

class GameCharacterPriestState : public GameCharacterState
{
public:
	GameCharacterPriestState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};
