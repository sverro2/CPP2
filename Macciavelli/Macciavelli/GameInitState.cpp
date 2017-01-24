#include "GameInitState.h"
#include "GameContext.h"
#include "CardReader.h"

void GameInitState::EnterState()
{
	_context.ShuffleBuildingCards(std::move(CardReader::ReadBuildings("Data/Bouwkaarten.csv")));
	std::vector<Character> characters{ std::move(CardReader::ReadCharacters("Data/karakterkaaten.csv")) };
	std::vector<std::string> options;
	options.push_back("young");
	options.push_back("old");
	int item{ _server.RequestIntWithinRange("sven", "How old are you?", 0, 10) };
	_server.SendMessage("sven", "well you asked me: " + std::to_string(item));
}

void GameInitState::LeaveState()
{
}
