#include "GameCharacterMagicianState.h"
#include "Character.h"
#include "GameContext.h"

GameCharacterMagicianState::GameCharacterMagicianState(GameContext & context, IServer & server) : GameCharacterState{ context, server, CharacterType::MAGICIAN }
{
}

int GameCharacterMagicianState::CalculateBonusIncome()
{
	return 0;
}

void GameCharacterMagicianState::DoCharacterAction()
{
	auto player_name = _context.GetCurrentPlayer()->GetName();

	std::vector<std::string> magician_options = {
		"Trade with opponent (you have: " + std::to_string(_context.GetCurrentPlayer()->LookAtBuildingsInHand().size()) + " building cards, your opponent has: " + std::to_string(_context.GetPlayerAtRightHandOfCurrent()->LookAtBuildingsInHand().size()) + ")",
		"Trade with deck."
	};

	int option_index = _server.RequestOptionByIndex(player_name, magician_options, "What do you want to do?");

	//Trade with opponent.
	if (option_index == 0)
	{
		auto temp_building_cards = _context.GetCurrentPlayer()->LookAtBuildingsInHand();

		//Set opponent's building cards as own building cards.
		_context.GetCurrentPlayer()->SwapBuildingCards(_context.GetPlayerAtRightHandOfCurrent()->LookAtBuildingsInHand());

		//Set previously owned cards as opponent's building cards.
		_context.GetPlayerAtRightHandOfCurrent()->SwapBuildingCards(temp_building_cards);
	}
	//Trade with deck
	else
	{
		bool done = false;
		int cards_ditched = 0;

		while (!done)
		{
			std::vector<std::string> options = { "Yes", "No" };

			int option_index = _server.RequestOptionByIndex(_context.GetCurrentPlayer()->GetName(), options, "Do you want to ditch (another) building card?");

			//Yes.
			if (option_index == 0)
			{
				//Fetching building cards.
				auto current_building_cards = _context.GetCurrentPlayer()->LookAtBuildingsInHand();

				std::vector<std::string> ditch_options;

				for (int i = 0; i < current_building_cards.size(); i++)
				{
					ditch_options.push_back("Building: " + current_building_cards[i].GetName() + " cost to build: " + std::to_string(current_building_cards[i].GetCost()) + " color: " + ColorToString(current_building_cards[i].GetColor()));
				}

				//Fetch chosen building index.
				int ditch_index = _server.RequestOptionByIndex(_context.GetCurrentPlayer()->GetName(), ditch_options, "Which building do you want to ditch?");
			
				//Ditch card.
				current_building_cards.erase(current_building_cards.begin() + ditch_index);
				_context.GetCurrentPlayer()->SwapBuildingCards(current_building_cards);

				//If all building cards are ditched, then ditching is done.
				if (_context.GetCurrentPlayer()->LookAtBuildingsInHand().size() == 0)
				{
					done = true;
				}

				//Mark one more card ditched.
				cards_ditched++;
			}
			//No
			else 
			{
				done = true;
			}
		}

		//Fetch new building cards.
		for (int i = 0; i < cards_ditched; i++)
		{
			//Take building card from deck and add to player's hand.
			_context.GetCurrentPlayer()->AddBuilding(_context.TakeBuildingCard());
		}
	}
}
