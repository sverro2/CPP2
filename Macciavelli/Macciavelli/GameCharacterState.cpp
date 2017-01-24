#include "GameCharacterState.h"
#include "GameContext.h"

GameCharacterState::GameCharacterState(GameContext & _context, IServer & _server) : GameState{_context, _server}
{
}

void GameCharacterState::EnterState()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	

}

void GameCharacterState::LeaveState()
{
}
