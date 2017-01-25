#pragma once
#include "GameCharacterState.h"

class GameCharacterMagicianState : public GameCharacterState
{
public:
	GameCharacterMagicianState(GameContext& context, IServer& server);

private:
	// Inherited via GameCharacterState
	virtual int CalculateBonusIncome() override;
	virtual void DoCharacterAction() override;
};

