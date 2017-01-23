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
	string requestString(string player_name, string question);
	int requestInt(string player_name, string question);
	int requestIntWithinRange(string player_name, string question, int min, int max);
	int requestOptionByIndex(string player_name, vector<string> options, string question);

	//Notifications to client.
	void sendMessage(string player_name, string message);
	void sendMessage(vector<string> player_names, string message);

	void startListening(int port);

private:
	bool _running = true;
	string _prompt = "machiavelli> ";
	Sync_queue<ClientCommand> _queue;
	map<string, shared_ptr<ClientInfo>> _clients;

	void consume_command();
	void handle_client(Socket client);
	shared_ptr<ClientInfo> init_client_session(Socket client);
};

