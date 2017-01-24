#include "GameContext.h"
#include "IServer.h"
#include "GameInitState.h"

GameContext::GameContext(IServer& server) : _server{ server }
{
	InitGame();
}

void GameContext::SwitchToState(std::unique_ptr<GameState> state)
{
	//Notify old state to start the "LeaveState"
	if (_current_gamestate != nullptr) {
		_current_gamestate->LeaveState();
	}

	//Set new state
	_current_gamestate = std::move(state);

	//Start new state
	_current_gamestate->EnterState();
}

const std::vector<Player> GameContext::GetPlayers() const
{
	return _players;
}

void GameContext::InitGame()
{
	SwitchToState(std::move(std::make_unique<GameInitState>(*this, _server)));
}
