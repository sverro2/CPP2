#pragma once
#include <string>
#include <vector>
using namespace std;

class IServer
{
public:
	//Request result value from client.
	virtual const string RequestString(const string player_name, const string question) = 0;
	virtual const int RequestInt(const string player_name, const string question) = 0;
	virtual const int RequestIntWithinRange(const string player_name, string question, int min, int max) = 0;
	virtual const int RequestOptionByIndex(const string player_name, const vector<string> options, const string question) = 0;

	//Notifications to client.
	virtual void SendMessage(const string player_name, const string message) = 0;
	virtual void SendMessage(const vector<string> player_names, const string message) = 0;
	virtual void SendMessageToAll(const string message) = 0;
	virtual void SendMessageToAllBut(const string player_name, const string message) = 0;

	//Get player names
	virtual const std::vector<std::string> GetPlayers() = 0;

	virtual ~IServer() {};
};

