#pragma once
#include "GameCharacterState.h"

class GameCharacterKingState : public GameCharacterState
{
public:
	GameCharacterKingState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

