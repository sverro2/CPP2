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
#include "Player.h"
#include "ClientInfo.h"

using namespace std;

class Server
{
public:
	Server();

	//Request result value from client.
	const string requestString(const string player_name, const string question); 
	const int requestInt(const string player_name, const string question);
	const int requestIntWithinRange(const string player_name, string question, int min, int max);
	const int requestOptionByIndex(const string player_name, const vector<string> options, const string question);

	//Notifications to client.
	void sendMessage(const string player_name, const string message);
	void sendMessage(const vector<string> player_names, const string message);

	void startListening(const int port);

private:
	bool _running = true;
	string _prompt = "machiavelli> ";
	Sync_queue<ClientCommand> _queue;
	map<string, shared_ptr<ClientInfo>> _clients;

	void consume_command();
	void handle_client(Socket client);
	shared_ptr<ClientInfo> init_client_session(Socket client);
};

