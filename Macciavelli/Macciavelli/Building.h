#pragma once
#include <string>
#include "Color.h"

class Building
{
public:
	Building();
	Building(const std::string name, const unsigned short cost, const Color color);

	//streaming
	friend std::istream &operator >> (std::istream &is, Building &r);
	friend std::ostream &operator << (std::ostream &is, const Building &r);
	const bool operator==(const Building& other) const;

	//getters
	const std::string GetName() const;
	const unsigned short GetCost() const;
	const Color GetColor() const;
	const std::string GetDescription() const;
private:
	std::string _name;
	unsigned short _cost;
	Color _color;
	std::string _description;
};

