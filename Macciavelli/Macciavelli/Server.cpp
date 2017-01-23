#include "Server.h"

Server::Server()
{
}

const string Server::requestString(const string player_name, const string question)
{
	_clients[player_name]->get_socket().write(question);
	string result;
	_clients[player_name]->get_socket().readline([&result](std::string input) {
		result = input;
	});
	return result;
}

const int Server::requestInt(const string player_name, const string question)
{
	sendMessage(player_name, question);
	try {
		int result;
		_clients[player_name]->get_socket().readline([&result](std::string input) {
			result = stoi(input);
		});
		return result;
	}
	catch (...) {
		sendMessage(player_name, "Invalid input given!");
		return this->requestInt(player_name, question);
	}
}

const int Server::requestIntWithinRange(const string player_name, const string question, const int min, const int max)
{
	sendMessage(player_name, question);
	try {
		int result;
		_clients[player_name]->get_socket().readline([&result](std::string input) {
			result = stoi(input);
		});

		if (result > max || result < min) {
			sendMessage(player_name, "Number not in range!");
			return this->requestIntWithinRange(player_name, question, min, max);
		}
		else {
			return result;
		}
	}
	catch (...) {
		sendMessage(player_name, "Invalid input given!");
		return this->requestIntWithinRange(player_name, question, min, max);
	}
}

const int Server::requestOptionByIndex(const string player_name, const vector<string> options, const string question)
{
	sendMessage(player_name, question);

	for (int i = 1; i <= options.size(); i++)
	{
		sendMessage(player_name, "[" + to_string(i) + "] " + options.at(i - 1));
	}

	try {
		int result;
		_clients[player_name]->get_socket().readline([&result](std::string input) {
			result = stoi(input);
		});
		if (result > options.size() || result < 1) {
			sendMessage(player_name, "Number not in range!");
			return this->requestOptionByIndex(player_name, options, question);
		}
		else {
			return result - 1;
		}
	}
	catch (...) {
		sendMessage(player_name, "Invalid input given!");
		return this->requestOptionByIndex(player_name, options, question);
	}
}

void Server::sendMessage(const string player_name, const string message)
{
	_clients[player_name]->get_socket().write(message);
}

void Server::sendMessage(const vector<string> player_names, const string message)
{
	for (int i = 0; i < player_names.size(); i++)
	{
		sendMessage(player_names[i], message);
	}
}

void Server::startListening(const int port)
{
	vector<thread> all_threads;
	// start command consumer thread

	all_threads.emplace_back([this] { consume_command(); });

	// create a server socket
	try {
		ServerSocket server{ port };
		cerr << "server listening" << '\n';
		while (_running) {
			// wait for connection from client; will create new socket
			server.accept([&all_threads, this](Socket client) {
				std::cerr << "Connection accepted from " << client.get_dotted_ip() << "\n";
				all_threads.emplace_back([&client, this] { handle_client(move(client)); });
			});
			this_thread::sleep_for(chrono::milliseconds(100));
		}
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

void Server::consume_command() // runs in its own thread
{
	try {
		while (_running) {
			ClientCommand command{ _queue.get() }; // will block here unless there are still command objects in the queue
			if (auto clientInfo = command.get_client_info().lock()) {
				auto &client = clientInfo->get_socket();
				auto &player = clientInfo->get_player();
				try {
					auto com = command.get_cmd();
						
						if (com == "Test")
						{
							auto result = requestString("HulkHogan", "Dit is een testvraag?");
							sendMessage(player.get_name(), result);
						}
						else
						{
						
						}


					client << player.get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << _prompt;
				}
				catch (const exception& ex) {
					cerr << "*** exception in consumer thread for player " << player.get_name() << ": " << ex.what() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
				catch (...) {
					cerr << "*** exception in consumer thread for player " << player.get_name() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
			}
		}
	}
	catch (...) {
		cerr << "consume_command crashed\n";
	}
}
//Hetzelfde
void Server::handle_client(Socket client) // this function runs in a separate thread
{
	try {
		auto client_info = init_client_session(move(client));
		auto &socket = client_info->get_socket();
		auto &player = client_info->get_player();

		socket << "Welcome, " << player.get_name() << ", have fun playing our game!\r\n" << _prompt;

		// Add client to the list of connected clients using the name as the identifier
		_clients.insert(std::pair <string, std::shared_ptr<ClientInfo>>(player.get_name(), client_info));

		while (_running) { // game loop
			try {
				// read first line of request
				std::string cmd;
				if (socket.readline([&cmd](std::string input) { cmd = input; })) {
					cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.get_name() << "] " << cmd << "\r\n";

					if (cmd == "quit") {
						socket.write("Bye!\r\n");
						break; // out of game loop, will end this thread and close connection
					}
					else if (cmd == "quit_server") {
						_running = false;
					}

					ClientCommand command{ cmd, client_info };
					_queue.put(command);
				};

			}
			catch (const exception& ex) {
				socket << "ERROR: " << ex.what() << "\r\n";
			}
			catch (...) {
				socket.write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
			}
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
	}
	return make_shared<ClientInfo>(move(client), Player{ name });
}