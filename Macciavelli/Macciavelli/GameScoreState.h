#pragma once
#include "GameState.h"

class GameScoreState : public GameState
{
public:
	using GameState::GameState;

	// Inherited via GameState
	virtual void EnterState() override;
	virtual void LeaveState() override;
};

