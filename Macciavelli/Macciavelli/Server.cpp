#include "Server.h"
#include "GameController.h"
#include "EndGame.h"

Server::Server()
{
}

const string Server::RequestString(const string player_name, const string question)
{
	_clients[player_name]->get_socket().write(question);
	string result{ ReadPlayerInput(player_name) };
	return result;
}

const int Server::RequestInt(const string player_name, const string question)
{
	SendMessage(player_name, question + "(input number)");
	try {
		int result{ stoi(ReadPlayerInput(player_name)) };
		return result;
	}
	catch (...) {
		SendMessage(player_name, "Invalid input given!");
		return this->RequestInt(player_name, question);
	}
}

const int Server::RequestIntWithinRange(const string player_name, const string question, const int min, const int max)
{
	std::string compiled_question{ question + "(" + std::to_string(min) + " - " + std::to_string(max) + ")" };
	SendMessage(player_name, compiled_question);
	try {
		int result{ stoi(ReadPlayerInput(player_name)) };

		if (result > max || result < min) {
			SendMessage(player_name, "Number not in range!");
			return this->RequestIntWithinRange(player_name, question, min, max);
		}
		else {
			return result;
		}
	}
	catch (...) {
		SendMessage(player_name, "Invalid input given!");
		return this->RequestIntWithinRange(player_name, question, min, max);
	}
}

const int Server::RequestOptionByIndex(const string player_name, const vector<string> options, const string question)
{
	SendMessage(player_name, question);
	std::string player_input;
	for (int i = 1; i <= options.size(); i++)
	{
		SendMessage(player_name, "[" + to_string(i) + "] " + options.at(i - 1));
	}

	try {
		player_input = ReadPlayerInput(player_name);
		int result{ stoi(player_input) };

		if (result > options.size() || result < 1) {
			SendMessage(player_name, "Number not in range!");
			return this->RequestOptionByIndex(player_name, options, question);
		}
		else {
			return result - 1;
		}
	}
	catch (...) {
		auto option_index_it{ std::find(options.begin(), options.end(), player_input) };

		if (option_index_it == options.end()) {
			SendMessage(player_name, "Invalid input given!");
			return this->RequestOptionByIndex(player_name, options, question);
		}
		else {
			return option_index_it - options.begin();
		}
	}
}

void Server::SendMessage(const string player_name, const string message)
{
	_clients[player_name]->get_socket().write(message + "\r\n");
}

void Server::SendMessage(const vector<string> player_names, const string message)
{
	for (int i = 0; i < player_names.size(); i++)
	{
		SendMessage(player_names[i], message);
	}
}

void Server::startListening(const int port)
{
	vector<thread> all_threads;

	// create a server socket
	try {
		ServerSocket server{ port };
		cerr << "server listening" << '\n';

		//init players
		while (_running) {
			// wait for connection from client; will create new socket
			server.accept([&all_threads, this](Socket client) {
				std::cerr << "Connection accepted from " << client.get_dotted_ip() << "\n";
				all_threads.emplace_back([&client, this] { handle_client(move(client)); });
			});
			this_thread::sleep_for(chrono::milliseconds(100));

			//when to players are added, the game can be started
			if (_clients.size() == 2) {
				break;
			}
		}

		//initialize game
		if (_running) {
			GameController game_controller(*this);

			//play game
			while (_running) {
				//make sure the game currently has two online players
				if (_clients.size() < 2) {
					break;
				}

				this_thread::sleep_for(chrono::milliseconds(100));
			}
		}

		std::cout << "Not enough players, quiting game now!" << std::endl;
	}
	catch (const EndGame& end_of_game) {
		std::cout << "Someone has ended our game... Quiting game..." << std::endl;
	}
	catch (const exception& ex) {
		cerr << ex.what() << ", resuming..." << '\n';
	}
	catch (...) {
		cerr << "problems, problems, but: keep calm and carry on!\n";
	}

	for (auto &t : all_threads) {
		t.join();
	}
}

void Server::handle_client(Socket client) // this function runs in a separate thread
{
	try {
		auto client_info = init_client_session(move(client));
		auto &socket = client_info->get_socket();
		auto &player = client_info->get_player();

		socket << "Welcome, " << player.get_name() << ", have fun playing our game!\r\n";

		// Add client to the list of connected clients using the name as the identifier
		_clients.insert(std::pair <string, std::shared_ptr<ClientInfo>>(player.get_name(), client_info));

		while (_running) { // game loop
			try {
				// read first line of request
				std::string cmd;
				if (socket.readline([&cmd](std::string input) { cmd = input; })) {
					cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.get_name() << "] " << cmd << "\r\n";

					if (cmd == "quit" || cmd == "quit_server") {
						socket.write("Bye!\r\n");
						for (const auto& client : _clients) {
							SendMessage(client.first, "Someone left... Bye! We hope you had some fun!");
						}
						_running = false;
					}

					//When the current player has inserted some input
					if (player.get_name() == _current_player) {
						ClientCommand command{ cmd, client_info, player };
						_queue.put(command);
					}
					else {
						SendMessage(player.get_name(), "Sorry, it's not your turn. Wait until your opponent has finished...");
					}
				};

			}
			catch (const exception& ex) {
				socket << "ERROR: " << ex.what() << "\r\n";
			}
			catch (...) {
				socket.write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
			}

			this_thread::sleep_for(chrono::milliseconds(100));
		}
		// close weg
	}
	catch (std::exception &ex) {
		cerr << "handle_client " << ex.what() << "\n";
	}
	catch (...) {
		cerr << "handle_client crashed\n";
	}
}

//Same
shared_ptr<ClientInfo> Server::init_client_session(Socket client) {
	client.write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
	client.write("What's your name?\r\n");
	client.write(_prompt);
	string name;
	bool done{ false };
	while (!done) {
		done = client.readline([&name](std::string input) {
			name = input;
		});
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	return make_shared<ClientInfo>(move(client), Client{ name });
}

const std::string Server::ReadPlayerInput(const std::string & const player)
{
	//create prompt for user
	_clients[player]->get_socket().write(_prompt);

	//set current player
	_current_player = player;

	ClientCommand command{ _queue.get() };

	if (!_running) {
		throw EndGame();
	}

	//return command string
	std::string input{ command.get_cmd() };
	return std::move(input);
}
