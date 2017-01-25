#include "GameCharacterState.h"
#include "GameContext.h"

GameCharacterState::GameCharacterState(GameContext & _context, IServer & _server) : GameState{_context, _server}
{
}

void GameCharacterState::EnterState()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	
	std::vector<std::string> base_options;
	base_options.push_back("Show money and spawned buildings of a player?");
	base_options.push_back("Building cards you hold in you hand?");
	//look at the table
	

}

void GameCharacterState::LeaveState()
{
}

void GameCharacterState::ShowCardsInHand()
{
	//for(const auto& building : _context.GetCurrentPlayer()->)
}
