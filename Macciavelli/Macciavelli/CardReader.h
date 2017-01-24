#pragma once
#include <vector>
#include "Building.h"
#include "Character.h"

class CardReader
{
public:
	static const std::vector<Building> ReadBuildings(const char* building_file);
	static const std::vector<Building> ReadCharacters(const char* character_file);
};

