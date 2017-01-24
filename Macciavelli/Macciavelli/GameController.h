#pragma once

class IServer;
class GameController
{
public:
	GameController(IServer& server);
private:
	IServer& _server;
};

