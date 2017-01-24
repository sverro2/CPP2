#include "CardReader.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <exception>

std::vector<Building> CardReader::ReadBuildings(const char* building_file)
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

std::vector<Character> CardReader::ReadCharacters(const char* character_file)
{
	try {
		std::ifstream in(character_file);

		std::vector<Character> all_characters{ std::istream_iterator<Character>(in),{} };
		return std::move(all_characters);
	}
	catch (...) {
		std::cerr << "Sorry, but we could not load the buildings file" << std::endl;
		return std::vector<Character>();
	}
}
