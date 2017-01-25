#pragma once
#include <memory>
#include "GameState.h"
#include "Character.h"
#include "Player.h"

class GameCharacterState : public GameState
{
public:
	GameCharacterState(GameContext& _context, IServer& _server, CharacterType type, const size_t max_amount_of_buildings_to_build = 1);

	// Inherited via GameState
	virtual void EnterState() override;
	virtual void LeaveState() override;
private:
	CharacterType _type;
	size_t _max_amount_of_buildings_to_build;

	virtual int CalculateBonusIncome() = 0;
	virtual void DoCharacterAction() = 0;
	void ShowCurrentPlayerBuildingCards();
	void ShowBalance(const std::shared_ptr<Player> player_to_look_at);
	void ShowTotalScore(const std::shared_ptr<Player> player_to_look_at);
	void ShowAmoundOfCardsInHand(const std::shared_ptr<Player> player_to_look_at);
	void ShowConstructedBuildings(const std::shared_ptr<Player> player_to_look_at);
	void ShowTableOfPlayer(const std::shared_ptr<Player> player_to_look_at);
	void ShowChoiceCoinsOrBuildingCards();
	void ShowOptionToConstructBuilding();
};

