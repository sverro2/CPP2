#include "GameCharacterArchitectState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterArchitectState::GameCharacterArchitectState(GameContext & context, IServer & server) : GameCharacterState{context, server, CharacterType::ARCHITECT, 3}
{
}

int GameCharacterArchitectState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterArchitectState::DoCharacterAction()
{
	auto current_player{ _context.GetCurrentPlayer() };
	_server.SendMessage(current_player->GetName(), "As an architect you are able to build up to 3 buildings in your game-round.");
	_server.SendMessage(current_player->GetName(), "Besides that, you also received 2 building cards.");
	
	for (int x{ 0 }; x < 2; x++) {
		current_player->AddBuilding(_context.TakeBuildingCard());
	}
}
