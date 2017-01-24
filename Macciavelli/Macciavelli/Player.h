#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Character.h"

class Player
{
public:
	Player(const std::string name, const unsigned short age);

	//getters
	const std::string& GetName() const;
	const unsigned short GetAge() const;
	const std::vector<std::shared_ptr<Character>>& GetCharacters();

	//add character
	void AddCharacter(const std::shared_ptr<Character>& character);
	void ResetCharacters();

private:
	const std::string _name;
	const unsigned short _age;
	std::vector<std::shared_ptr<Character>> _characters;
};

