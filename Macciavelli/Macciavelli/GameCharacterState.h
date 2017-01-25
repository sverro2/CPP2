#pragma once
#include "GameState.h"
class GameCharacterState : public GameState
{
public:
	GameCharacterState(GameContext& _context, IServer& _server);

	// Inherited via GameState
	virtual void EnterState() override;
	virtual void LeaveState() override;
private:
	virtual int CalculateBonusIncome() = 0;
	virtual void DoCharacterAction() = 0;
	void ShowCardsInHand();
	void ShowTableOfPlayer();
};

