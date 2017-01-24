#pragma once
#include <vector>

class IServer;
class GameContext
{
public:
	GameContext(IServer& server);
private:
	IServer& _server;
	std::vector<std::string> _players;
	std::string _current_player;

	void InitGame();
};

