#include "GameCharacterState.h"
#include "GameContext.h"
#include "Color.h"

GameCharacterState::GameCharacterState(GameContext & _context, IServer & _server, CharacterType type) : GameState{_context, _server}, _type{type}
{
}

void GameCharacterState::EnterState()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	
	//Show for everyone the current character.
	_server.SendMessageToAll("The active character is: " + Character::CharacterEnumToString(_type));

	std::vector<std::string> base_options;
	base_options.push_back("Show money and spawned buildings of a player?");
	base_options.push_back("Building cards you hold in you hand?");

	//Ask the user to view some items.
	ShowTableOfPlayer();

	//Add bonus money.
	current_player->MutateMoney(CalculateBonusIncome());

	//Execute special character action.
	DoCharacterAction();

	//Ask user to get an extra card or 2 gold.
	ShowChoiceCoinsOrBuildingCards();

	//The option to build something.
	if (_context.GetCurrentPlayer()->LookAtBuildingsInHand().size() > 0)
	{
		ShowOptionToConstructBuilding();
	}
}

void GameCharacterState::LeaveState()
{
}

void GameCharacterState::ShowBalance()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "Your balance is: " + std::to_string(_context.GetCurrentPlayer()->GetMoney()) + " coins.");
}

void GameCharacterState::ShowTotalScore()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "Your total score is: " + std::to_string(_context.GetCurrentPlayer()->GetScore()));
}

void GameCharacterState::ShowCardsInHand()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "Your building cards are:");

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

void GameCharacterState::ShowConstructedBuildings()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "Your constructed buildingss are:");

	for (const auto& building : _context.GetCurrentPlayer()->LookAtConstructedBuildings()) {
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

void GameCharacterState::ShowTableOfPlayer()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };

	std::vector<std::string> options = { "Balance.", "Constructed buildings", "Building cards", "Total score" };

	int option_index = _server.RequestOptionByIndex(player_name, options, "What do you wish to view?");

	switch (option_index)
	{
	case 0:
		//Show the player's balance.
		ShowBalance();
		break;
	case 1:
		//Show the player's constructed buildings.
		ShowConstructedBuildings();
		break;
	case 2:
		//Show the player's building cards.
		ShowCardsInHand();
		break;
	default:
		//Show the player's total score.
		ShowTotalScore();
		break;
	}
}

void GameCharacterState::ShowChoiceCoinsOrBuildingCards()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };

	std::vector<std::string> options = { "I want a building card.", "I want money." };

	int choice = _server.RequestOptionByIndex(player_name, options, "Do you want to earn a building card or money?");

	//Choice = Building card.
	if (choice == 0)
	{
		//Retrieve two buildings.
		std::vector<Building> buildings = { _context.TakeBuildingCard(), _context.TakeBuildingCard() };

		//The question strings.
		std::vector<string> building_questions;

		for (int i = 0; i < buildings.size(); i++)
		{
			//Building the question string.
			building_questions.push_back(buildings[i].GetName() + ": this building costs " + std::to_string(buildings[i].GetCost()) + " and has the color " + ColorToString(buildings[i].GetColor()));
		}

		//Get the chosen building index.
		int building_index = _server.RequestOptionByIndex(player_name, building_questions, "You've picked two building cards. Which of these two do you want to keep?");

		//Add building to hand.
		_context.GetCurrentPlayer()->AddBuilding(buildings[building_index]);
		_server.SendMessage(player_name, "You've built: " + buildings[building_index].GetName());
		_server.SendMessageToAllBut(player_name, "Player: " + player_name + " has constructed: " + buildings[building_index].GetName() = " and it did cost " + std::to_string(buildings[building_index].GetCost()) + " coins.");
	}
	//Choice = Money.
	else
	{
		//Earn 2 coins.
		_context.GetCurrentPlayer()->EarnMoney(2);
		_server.SendMessage(player_name, "You've earned 2 coins. Your new balance is: " + std::to_string(_context.GetCurrentPlayer()->GetMoney()) + " coins.");
		_server.SendMessageToAllBut(player_name, "Player: " + player_name + " has earned 2 coins. The player's new balance is: " + std::to_string(_context.GetCurrentPlayer()->GetMoney()) + " coins.");
	}
}

void GameCharacterState::ShowOptionToConstructBuilding()
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };

	auto buildings = _context.GetCurrentPlayer()->LookAtBuildingsInHand();

	//The construction options.
	std::vector<string> construction_options;

	for (int i = 0; i < buildings.size(); i++)
	{
		//Building the construction options string.
		construction_options.push_back(buildings[i].GetName() + ": this building costs " + std::to_string(buildings[i].GetCost()) + " and has the color " + ColorToString(buildings[i].GetColor()));
	}
	
	//Fetch chosen building index.
	int building_index = _server.RequestOptionByIndex(player_name, construction_options, "Which building do you want to construct?");

	//If player cannot afford this building.
	if (buildings[building_index].GetCost() > _context.GetCurrentPlayer()->GetMoney())
	{
		_server.SendMessage(player_name, "You cannot afford this building! Your balance is: " + std::to_string(_context.GetCurrentPlayer()->GetMoney()) + " and the building costs: " + std::to_string(buildings[building_index].GetCost()) + " coins.");
	}
	//Player can afford this building.
	else
	{
		//If building is built.
		if (_context.GetCurrentPlayer()->ConstructBuilding(buildings[building_index]))
		{
			auto building = buildings[building_index];
			_server.SendMessage(player_name, "You've built: " + building.GetName());
			_server.SendMessageToAllBut(player_name, "Player: " + player_name + " has constructed: " + building.GetName() = " and it did cost " + std::to_string(building.GetCost()) + " coins.");
		}
	}
}
