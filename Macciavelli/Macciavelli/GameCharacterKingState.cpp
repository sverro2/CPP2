#include <algorithm>
#include "GameCharacterKingState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterKingState::GameCharacterKingState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::KING }
{
}

int GameCharacterKingState::CalculateBonusIncome()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	auto count{ std::count_if(current_player->LookAtConstructedBuildings().begin(), current_player->LookAtConstructedBuildings().end(), [](const Building& building) {return building.GetColor() == Color::GOLD; }) };
	_server.SendMessage(current_player->GetName(), "You are our King. We noticed you have built " + std::to_string(count) + " golden buildings. Therefore you are gifted " + std::to_string(count) + " gold.");
	return count;
}

void GameCharacterKingState::DoCharacterAction()
{
}
