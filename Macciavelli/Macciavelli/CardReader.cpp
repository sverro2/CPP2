#include "CardReader.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <exception>

const std::vector<Building> CardReader::ReadBuildings(const char* building_file)
{	
	try {
		std::ifstream in(building_file);

		std::vector<Building> all_buildings{ std::istream_iterator<Building>(in),{} };
		return std::move(all_buildings);
	}
	catch (...) {
		std::cerr << "Sorry, but we could not load the buildings file" << std::endl;
		return std::vector<Building>();
	}
}

const std::vector<Building> CardReader::ReadCharacters(const char* character_file)
{
	std::vector<Building> all_characters;
	return std::move(all_characters);
}