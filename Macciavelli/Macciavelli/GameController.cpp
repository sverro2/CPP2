#include "GameController.h"
#include "IServer.h"

GameController::GameController(IServer& server) : _server{ server }
{
	std::vector<std::string> options;
	options.push_back("young");
	options.push_back("old");
	int item{ _server.RequestOptionByIndex("sven", options, "How old are you?")};
	_server.SendMessage("sven", "well you asked me: " + options[item]);
}
