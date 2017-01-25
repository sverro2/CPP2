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
	auto& current_player{ _context.GetCurrentPlayer() };

	//If the opponent does not have any buildings constructed.
	if (_context.GetPlayerAtRightHandOfCurrent()->LookAtConstructedBuildings().size() == 0)
	{
		_server.SendMessage(current_player->GetName(), "Your opponent does not have any buildings constructed.");
	}
	else
	{
		//Fetch oponent's constructed buildings.
		auto oponent_buildings = _context.GetPlayerAtRightHandOfCurrent()->LookAtConstructedBuildings();

		std::vector<std::string> demolition_options;

		for (int i = 0; i < oponent_buildings.size(); i++)
		{
			//If player can afford to demolish this building.
			if (oponent_buildings[i].GetCost() - 1 <= current_player->GetMoney())
			{
				demolition_options.push_back(oponent_buildings[i].GetName() + " (cost to destory: " + std::to_string(oponent_buildings[i].GetCost() - 1) + " coins)");
			}
		}

		//If there are no buildings which can be afforded to demolish.
		if (demolition_options.size() == 0)
		{
			_server.SendMessage(current_player->GetName(), "You do not have enough coins for any demolition");
		}
		//If there are buildings which can be afforded to demolsih.
		else
		{
			//Get the about to demolish building index.
			int building_index = _server.RequestOptionByIndex(current_player->GetName(), demolition_options, "Which building do you want to destroy?");

			//Remove cost of demolition from current players money.
			current_player->MutateMoney(oponent_buildings[building_index].GetCost() - 1);

			//Demolish building from opponents building_area.
			_context.GetPlayerAtRightHandOfCurrent()->DemolishBuilding(building_index);
		}
	}
}