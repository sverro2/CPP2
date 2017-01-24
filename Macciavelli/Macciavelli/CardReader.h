#pragma once
#include <vector>
#include "Building.h"
#include "Character.h"

class CardReader
{
public:
	static std::vector<Building> ReadBuildings(const char* building_file);
	static std::vector<Character> ReadCharacters(const char* character_file);
};

