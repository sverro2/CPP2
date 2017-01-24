#include "GameInitState.h"

void GameInitState::EnterState()
{
	std::vector<std::string> options;
	options.push_back("young");
	options.push_back("old");
	int item{ _server.RequestIntWithinRange("sven", "How old are you?", 0, 10) };
	_server.SendMessage("sven", "well you asked me: " + std::to_string(item));
}

void GameInitState::LeaveState()
{
}