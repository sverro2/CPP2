#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "GameState.h"

class IServer;
class GameContext
{
public:
	GameContext(IServer& server);
	void SwitchToState(std::unique_ptr<GameState> _state);
	const std::vector<Player> GetPlayers() const;
private:
	IServer& _server;
	std::vector<Player> _players;
	std::string _current_player;

	void InitGame();
	std::unique_ptr<GameState> _current_gamestate;
};

