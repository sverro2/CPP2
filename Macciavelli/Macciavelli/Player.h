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
	const std::vector<std::shared_ptr<Character>>& GetCharacters();
	const int GetScore() const;

	//Add Building card to hand.
	void AddBuilding(const std::shared_ptr<Building>& building);

	//Add character card to hand.
	void AddCharacter(const std::shared_ptr<Character>& character);

	//Constructs a building from hand, returns bool if constructed.
	const bool ConstructBuilding(const std::shared_ptr<Building>& building);

	//Resets all characters.
	void ResetCharacters();

private:
	const std::string _name;
	const unsigned short _age;
	bool _first_to_eight_buildings;

	//The playable roles.
	std::vector<std::shared_ptr<Character>> _characters;

	//The building cards currently in hand.
	std::vector<std::shared_ptr<Building>> _available_buildings;

	//The constructed buildings.
	std::vector<std::shared_ptr<Building>> _building_area;
};

