#pragma once
#include "IServer.h"

class GameContext;

class GameState
{
public:
	GameState(GameContext& _context, IServer& _server);
	virtual void EnterState() = 0;
	virtual void LeaveState() = 0;
	virtual ~GameState() {};
protected:
	GameContext& _context;
	IServer& _server;
};

