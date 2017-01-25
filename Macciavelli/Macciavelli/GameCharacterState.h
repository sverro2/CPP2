#pragma once
#include "GameState.h"
#include "Character.h"
class GameCharacterState : public GameState
{
public:
	GameCharacterState(GameContext& _context, IServer& _server, CharacterType type);

	// Inherited via GameState
	virtual void EnterState() override;
	virtual void LeaveState() override;
private:
	CharacterType _type;

	virtual int CalculateBonusIncome() = 0;
	virtual void DoCharacterAction() = 0;
	void ShowBalance();
	void ShowTotalScore();
	void ShowCardsInHand();
	void ShowConstructedBuildings();
	void ShowTableOfPlayer();
	void ShowChoiceCoinsOrBuildingCards();
	void ShowOptionToConstructBuilding();
};

