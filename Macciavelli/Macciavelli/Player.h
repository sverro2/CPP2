#pragma once
#include <string>
class Player
{
public:
	Player(const std::string name, const unsigned short age);

	//getters
	const std::string& GetName() const;
	const unsigned short GetAge() const;
private:
	const std::string _name;
	const unsigned short _age;

};

