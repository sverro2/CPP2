#pragma once
#include "Color.h"
#include <iostream>
#include <string>

enum CharacterType {
	MURDERER,
	THIEF,
	MAGICIAN,
	KING,
	PRIEST,
	MERCHANT,
	ARCHITECT,
	CONDONTIERE
};

class Character
{
public:
	Character();
	Character(size_t index, CharacterType type);
	const bool operator==(const Character& character) const;

	static const CharacterType CharacterStringToEnum(const char* const name_string);
	const std::string GetCharacterName() const;

	//streaming
	friend std::istream &operator >> (std::istream &is, Character &character);
	friend std::ostream &operator << (std::ostream &is, const Character &character);

	//getters
private:
	size_t _index;
	CharacterType _type;
};

