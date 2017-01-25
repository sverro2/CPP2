#pragma once
#include "GameCharacterState.h"

class GameCharacterThiefState : public GameCharacterState
{
public:
	GameCharacterThiefState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

