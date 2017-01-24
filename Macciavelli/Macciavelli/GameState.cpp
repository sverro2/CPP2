#include "GameState.h"

GameState::GameState(GameContext & context, IServer & server) :
	_context{context}, _server{server}
{
}
