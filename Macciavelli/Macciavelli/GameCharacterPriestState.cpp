#include <algorithm>
#include "GameCharacterPriestState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterPriestState::GameCharacterPriestState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::PRIEST }
{
}

int GameCharacterPriestState::CalculateBonusIncome()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	auto count{ std::count_if(current_player->LookAtConstructedBuildings().begin(), current_player->LookAtConstructedBuildings().end(), [](const Building& building) {return building.GetColor() == Color::BLUE; }) };
	_server.SendMessage(current_player->GetName(), "You are our priest. We noticed you have built " + std::to_string(count) + " blue buildings. Therefore you are gifted " + std::to_string(count) + " gold.");
	return count;
}

void GameCharacterPriestState::DoCharacterAction()
{
}
