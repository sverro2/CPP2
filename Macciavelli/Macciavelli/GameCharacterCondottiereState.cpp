#include <algorithm>
#include "GameCharacterCondottiereState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterCondottiereState::GameCharacterCondottiereState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::CONDONTIERE }
{
}

int GameCharacterCondottiereState::CalculateBonusIncome()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	auto count{ std::count_if(current_player->LookAtConstructedBuildings().begin(), current_player->LookAtConstructedBuildings().end(), [](const Building& building) {return building.GetColor() == Color::RED; }) };
	_server.SendMessage(current_player->GetName(), "You are a condottiere. We noticed you have built " + std::to_string(count) + " red buildings. Therefore you are gifted " + std::to_string(count) + " gold.");
	return count;
}

void GameCharacterCondottiereState::DoCharacterAction()
{
}