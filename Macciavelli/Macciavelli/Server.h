#pragma once
#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <chrono>
#include <map>

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Client.h"
#include "ClientInfo.h"
#include "IServer.h"

using namespace std;

class Server : public IServer
{
public:
	Server();

	//Request result value from client.
	const string RequestString(const string player_name, const string question) override; 
	const int RequestInt(const string player_name, const string question) override;
	const int RequestIntWithinRange(const string player_name, string question, int min, int max) override;
	const int RequestOptionByIndex(const string player_name, const vector<string> options, const string question) override;

	//Notifications to client.
	void SendMessage(const string player_name, const string message) override;
	void SendMessage(const vector<string> player_names, const string message) override;

	void startListening(const int port);

	//getters
	const map<string, shared_ptr<ClientInfo>>& GetClients() const;

private:
	bool _running = true;
	bool _game_started = false;
	string _prompt = "machiavelli> ";
	Sync_queue<ClientCommand> _queue;
	map<string, shared_ptr<ClientInfo>> _clients;

	//void consume_command();
	void handle_client(Socket client);
	shared_ptr<ClientInfo> init_client_session(Socket client);

	const std::string ReadPlayerInput(const std::string& player);

	std::string _current_player = "";
};

