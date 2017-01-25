#pragma once
#include "GameCharacterState.h"

class GameCharacterMurdererState : public GameCharacterState
{
public:
	GameCharacterMurdererState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};