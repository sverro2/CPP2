#include <algorithm>
#include "GameInitState.h"
#include "GameContext.h"
#include "CardReader.h"
#include "EndGame.h"

void GameInitState::EnterState()
{
	_context.ShuffleBuildingCards(std::move(CardReader::ReadBuildings("Data/Bouwkaarten.csv")));
	std::vector<Character> characters{ std::move(CardReader::ReadCharacters("Data/karakterkaarten.csv")) };

	if (!_context.HasBuildingCards() || characters.empty()) {
		std::cout << "Check your CSV file configuration." << std::endl;
		_server.SendMessageToAll("Server is not cofigured correctly (CSV FILE(PATH) INCORRECT)...");
		throw EndGame();
	}

	//initialize character deck
	std::sort(characters.begin(), characters.end(), [](const Character& a, const Character& b) {
		return a.GetIndex() < b.GetIndex();
	});

	//initialize players
	const auto clients{ _server.GetPlayers() };

	int oldest{ 0 };
	std::shared_ptr<Player> oldest_player;

	for (const auto& client : clients) {
		const int age{ _server.RequestIntWithinRange(client, "What is your age?", 10, 100) };
		const auto created_player{ std::make_shared<Player>(client, age) };
		_context.AddPlayer(created_player);

		if (age > oldest) {
			oldest_player = created_player;
			oldest = age;
		}
	}

	//set king to oldest player
	auto& king{ _context.GetKingReference() };
	king = std::make_unique<King>(oldest_player);

	auto king_name{ king->GetKing()->GetName() };
	_server.SendMessage(king_name, "You are the oldest player. Congratulations, you are king.");
	_server.SendMessageToAllBut(king_name, "The game has begun. " + king_name + " has been selected as your king.");	

	//set character deck (right order/available characters)
	_context.SetCharacterDeck(std::move(characters));
}

void GameInitState::LeaveState()
{
	_server.SendMessageToAll("The king has been choosen. The game will start momentarely");
}
