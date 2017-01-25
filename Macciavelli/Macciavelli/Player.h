#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Character.h"
#include "Building.h"

class Player
{
public:
	Player(const std::string name, const unsigned short age);

	//Getters
	const std::string& GetName() const;
	const unsigned short GetAge() const;
	const std::vector<Character>& GetCharacters();
	const int GetScore() const;
	const int GetMoney() const;
	const std::vector<Building>& LookAtBuildingsInHand() const;
	const std::vector<Building>& LookAtConstructedBuildings() const;
	const bool WasFirstToEightBuildings() const;

	//Has Character.
	const bool HasCharacter(const CharacterType character_type) const;

	//Add Building card to hand.
	void AddBuilding(const Building building);

	//Add character card to hand.
	void AddCharacter(const Character character);

	//Constructs a building from hand, returns bool if constructed.
	const bool ConstructBuilding(const Building building);

	//Deomishes a building by index.
	void DemolishBuilding(const unsigned short index);

	//Resets all characters.
	void ResetCharacters();

	//Money
	const bool MutateMoney(const unsigned short money_balance);
	void EarnMoney(const unsigned short amount);

	//Declare first to eight.
	void DeclareFirstToEight();
private:
	const std::string _name;
	const unsigned short _age;
	bool _first_to_eight_buildings;
	unsigned short _money = 2;

	//The playable roles.
	std::vector<Character> _characters;

	//The building cards currently in hand.
	std::vector<Building> _available_buildings;

	//The constructed buildings.
	std::vector<Building> _building_area;
};

