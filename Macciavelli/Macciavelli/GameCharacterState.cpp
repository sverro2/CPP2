#include "GameCharacterState.h"
#include "GameContext.h"
#include "Color.h"

GameCharacterState::GameCharacterState(GameContext & _context, IServer & _server, CharacterType type) : GameState{_context, _server}, _type{type}
{
}

void GameCharacterState::EnterState()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	
	//print for everyone what unit is currently playing

	std::vector<std::string> base_options;
	base_options.push_back("Show money and spawned buildings of a player?");
	base_options.push_back("Building cards you hold in you hand?");

	//ask the user to view some items ^^^^^^

	//Add bonus money
	current_player->MutateMoney(CalculateBonusIncome());

	//Execute special character action
	DoCharacterAction();

	//ask user to get an extra card or 2 gold

	//does user want to built something?
}

void GameCharacterState::LeaveState()
{
}

void GameCharacterState::ShowCardsInHand()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "You buildings are:");

	for (const auto& building : _context.GetCurrentPlayer()->LookAtBuildingsInHand()) {
		//color
		std::string color_string{ ColorToString(building.GetColor()) };
		std::string output{ "Color: " + color_string + "\r\n" };
		_server.SendMessage(player_name, output);

		//name / description
		_server.SendMessage(player_name, building.GetName() + " - " + building.GetDescription());
		_server.SendMessage(player_name, "You can buy this building for " + std::to_string(building.GetCost()) + " gold.");
		_server.SendMessage(player_name, "------------------------------");
	}
}
