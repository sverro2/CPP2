#include "Character.h"

Character::Character()
{
}

Character::Character(size_t index, CharacterType type) :
	_index{index},
	_type{type}
{
}

const CharacterType Character::CharacterStringToEnum(const char * const name_string)
{
	if (strcmp(name_string, "Moordenaar") == 0) {
		return CharacterType::MURDERER;
	}
	else if (strcmp(name_string, "Dief") == 0) {
		return CharacterType::THIEF;
	}
	else if (strcmp(name_string, "Magiër") == 0) {
		return CharacterType::MAGICIAN;
	}
	else if (strcmp(name_string, "Koning") == 0) {
		return CharacterType::KING;
	}
	else if (strcmp(name_string, "Prediker") == 0) {
		return CharacterType::PRIEST;
	}
	else if (strcmp(name_string, "Koopman") == 0) {
		return CharacterType::MERCHANT;
	}
	else if (strcmp(name_string, "Bouwmeester") == 0) {
		return CharacterType::ARCHITECT;
	}
	else {
		return CharacterType::CONDONTIERE;
	}
}

std::istream & operator >> (std::istream & is, Character & character)
{
	std::string index;
	std::getline(is, index, ';');
	character._index = atoi(index.c_str());

	//read color
	std::string type;
	std::getline(is, type);
	character._type = Character::CharacterStringToEnum(type.c_str());
	return is;
}

std::ostream & operator<<(std::ostream & is, const Character & character)
{
	is << character._index << ";" << character._type;
	return is;
}
