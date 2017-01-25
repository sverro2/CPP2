#include "GameCharacterState.h"
#include "GameContext.h"
#include "GameCharacterInitState.h"
#include "Color.h"

GameCharacterState::GameCharacterState(GameContext & _context, IServer & _server, CharacterType type) : GameState{_context, _server}, _type{type}
{
}

void GameCharacterState::EnterState()
{
	auto& current_player{ _context.GetCurrentPlayer() };
	//Show everyone the current character.
	_server.SendMessageToAll("The active character is: " + Character::CharacterEnumToString(_type));

	//choose a player you want to take a look at.
	std::vector<std::string> player_string;
	
	for (const auto& player : _context.GetPlayers()) {
		player_string.push_back(player->GetName());
	}

	int player_index{ _server.RequestOptionByIndex(current_player->GetName(), player_string, "What player would you like to take a look at?") };
	const auto player_to_look_at{ _context.GetPlayers().at(player_index) };

	//Ask the user to view some items.
	ShowTableOfPlayer(player_to_look_at);

	//Add bonus money.
	current_player->MutateMoney(CalculateBonusIncome());

	//Execute special character action.
	DoCharacterAction();

	//Ask user to get an extra card or 2 gold.
	ShowChoiceCoinsOrBuildingCards();

	//The option to build something.
	if (_context.GetCurrentPlayer()->LookAtBuildingsInHand().size() > 0)
	{
		ShowCurrentPlayerBuildingCards();
		ShowOptionToConstructBuilding();
	}

	if (_context.GetAmountOfCharactersInGame() == _context.GetCurrentCharacterIndex() + 1) {
		_server.SendMessageToAll("All characters have been played... Next round.");
		_context.SwitchToState(std::move(std::make_unique<GameCharacterInitState>(_context, _server)));
	}
	else {
		_context.SwitchToNextCharacter();
	}
}

void GameCharacterState::LeaveState()
{
}

void GameCharacterState::ShowCurrentPlayerBuildingCards()
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

void GameCharacterState::ShowBalance(const std::shared_ptr<Player> player_to_look_at)
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "Your balance is: " + std::to_string(_context.GetCurrentPlayer()->GetMoney()) + " coins.");
}

void GameCharacterState::ShowTotalScore(const std::shared_ptr<Player> player_to_look_at)
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	std::string player_to_look_at_name{ player_to_look_at->GetName() };

	_server.SendMessage(player_name, player_to_look_at_name + "'s total score is: " + std::to_string(player_to_look_at->GetScore()));
}

void GameCharacterState::ShowAmoundOfCardsInHand(const std::shared_ptr<Player> player_to_look_at)
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	_server.SendMessage(player_name, "The Player has " + std::to_string(player_to_look_at->LookAtBuildingsInHand().size()) + " building cards in his hand");
}

void GameCharacterState::ShowConstructedBuildings(const std::shared_ptr<Player> player_to_look_at)
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };
	std::string player_to_look_at_name{ player_to_look_at->GetName() };
	_server.SendMessage(player_name, player_to_look_at_name + "'s constructed buildings are:");

	for (const auto& building : player_to_look_at->LookAtConstructedBuildings()) {
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

void GameCharacterState::ShowTableOfPlayer(const std::shared_ptr<Player> player_to_look_at)
{
	std::string player_name{ _context.GetCurrentPlayer()->GetName() };

	std::vector<std::string> options = { "Balance.", "Constructed buildings", "Ammount Of Cards In Hand", "Total score", "Go Back To Game"};

	bool back_to_game{ false };

	while (!back_to_game) {
		int option_index = _server.RequestOptionByIndex(player_name, options, "What do you wish to view?");

		switch (option_index)
		{
		case 0:
			//Show the player's balance.
			ShowBalance(player_to_look_at);
			break;
		case 1:
			//Show the player's constructed buildings.
			ShowConstructedBuildings(player_to_look_at);
			break;
		case 2:
			//Show the player's building cards.
			ShowAmoundOfCardsInHand(player_to_look_at);
			break;
		case 3:
			//Show the player's total score.
			ShowTotalScore(player_to_look_at);
			break;
		case 4:
			back_to_game = true;
		}
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
