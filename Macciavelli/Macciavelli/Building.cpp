#include "Building.h"
#include <string>
Building::Building() {}

Building::Building(const std::string name, const unsigned short cost, const Color color) : 
	_name{name}, 
	_cost{cost}, 
	_description{_description}
{
}

const bool Building::operator==(const Building & other) const
{
	return _name == other._name;
}

const std::string Building::GetName() const
{
	return _name;
}

const unsigned short Building::GetCost() const
{
	return _cost;
}

const Color Building::GetColor() const
{
	return _color;
}

const std::string Building::GetDescription() const
{
	return _description;
}

std::istream & operator >> (std::istream & is, Building & building)
{
	std::string name;
	std::getline(is, name, ';');
	building._name = name;

	//read cost
	std::string cost;
	std::getline(is, cost, ';');
	building._cost = atoi(cost.c_str());

	//read color
	std::string color;
	std::getline(is, color, ';');
	building._color = StringToColor(color.c_str());

	//description
	std::getline(is, building._description);
	return is ;
}

std::ostream & operator << (std::ostream & is, const Building & building)
{
	is << building._name << ";" << building._cost << ";" << ColorToString(building._color) << ";" << building._description;
	return is;
}