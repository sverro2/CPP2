#include "GameInitState.h"
#include "GameContext.h"
#include "CardReader.h"
#include "EndGame.h"

void GameInitState::EnterState()
{
	_context.ShuffleBuildingCards(std::move(CardReader::ReadBuildings("Data/Bouwkarten.csv")));
	std::vector<Character> characters{ std::move(CardReader::ReadCharacters("Data/karakterkaaten.csv")) };

	if (!_context.HasBuildingCards() || characters.empty()) {
		std::cout << "Check your CSV file configuration." << std::endl;
		_server.SendMessageToAll("Server is not cofigured correctly...");
		throw EndGame();
	}

	std::vector<std::string> options;
	options.push_back("young");
	options.push_back("old");
	int item{ _server.RequestIntWithinRange("sven", "How old are you?", 0, 10) };
	_server.SendMessage("sven", "well you asked me: " + std::to_string(item));
}

void GameInitState::LeaveState()
{
}
