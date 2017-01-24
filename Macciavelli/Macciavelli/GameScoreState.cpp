#include <memory>
#include "GameScoreState.h"
#include "GameInitState.h"
#include "GameContext.h"

void GameScoreState::EnterState()
{
	//Fetch all players.
	auto players = _context.GetPlayers();

	//Player with the highest score.
	std::shared_ptr<Player> player_with_highest_score;

	//Fetching the player with the highest score.
	for (int i = 0; i < players.size(); i++)
	{
		_server.SendMessage(players[i].GetName(), "Calculating score..");

		//First iteration through players.
		if (player_with_highest_score = nullptr)
		{
			player_with_highest_score = std::make_shared<Player>(players[i]);
		}
		else
		{
			//If this player has a higher score then the player_with_highest_score.
			if (player_with_highest_score->GetScore() < players[i].GetScore())
			{
				//Declare this player the player_with_highest_score.
				player_with_highest_score = std::make_shared<Player>(players[i]);
			}
		}
	}

	//Notify winner.
	_server.SendMessage(player_with_highest_score->GetName(), "Congratulations you won this game! Your score was: " + std::to_string(player_with_highest_score->GetScore()));

	//Notify others.
	_server.SendMessageToAllBut(player_with_highest_score->GetName(), player_with_highest_score->GetName() + " has won this game with a score of: " + std::to_string(player_with_highest_score->GetScore()));

	//Switch to GameInitState state.
	_context.SwitchToState(std::move(std::make_unique<GameInitState>(_context, _server)));
}

void GameScoreState::LeaveState()
{
}
