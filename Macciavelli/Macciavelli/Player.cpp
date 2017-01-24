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
