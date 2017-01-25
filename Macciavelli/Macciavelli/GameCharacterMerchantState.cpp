#include <algorithm>
#include "GameCharacterMerchantState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterMerchantState::GameCharacterMerchantState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::MERCHANT }
{
}

int GameCharacterMerchantState::CalculateBonusIncome()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	auto count{ std::count_if(current_player->LookAtConstructedBuildings().begin(), current_player->LookAtConstructedBuildings().end(), [](const Building& building) {return building.GetColor() == Color::GREEN; }) };
	_server.SendMessage(current_player->GetName(), "You are a merchant, making lots of money. We noticed you have built " + std::to_string(count) + " green buildings. Therefore you are gifted " + std::to_string(count) + " gold.");
	_server.SendMessage(current_player->GetName(), "On top of that you have received one extra goldpiece, just because you're a merchant");
	return count + 1;
}

void GameCharacterMerchantState::DoCharacterAction()
{
}
