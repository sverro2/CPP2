#include "Player.h"

Player::Player(const std::string name, const unsigned short age) :
	_name{ name },
	_age{ age }
{
}

const std::string & Player::GetName() const
{
	return _name;
}

const unsigned short Player::GetAge() const
{
	return _age;
}

const std::vector<std::shared_ptr<Character>>& Player::GetCharacters()
{
	return _characters;
}

void Player::AddCharacter(const std::shared_ptr<Character>& character)
{
	_characters.push_back(character);
}

void Player::ResetCharacters()
{
	_characters.clear();
}
