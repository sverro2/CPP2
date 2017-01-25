#include "Player.h"
#include <map>
#include <algorithm>

Player::Player(const std::string name, const unsigned short age) :
	_name{ name },
	_age{ age }
{
	_first_to_eight_buildings = false;
}

const std::string & Player::GetName() const
{
	return _name;
}

const unsigned short Player::GetAge() const
{
	return _age;
}

const std::vector<Character>& Player::GetCharacters()
{
	return _characters;
}

const int Player::GetScore() const
{
	std::vector<Color> checked_collors;

	int score = 0;

	for (int i = 0; i < _building_area.size(); i++)
	{
		//Add building cost to score.
		score += _building_area[i].GetCost();

		//Color iterator for all building colors which are checked.
		const auto color_iterator{ std::find(checked_collors.begin(), checked_collors.end(), _building_area[i].GetColor()) };

		//If building color not marked as checked.
		if (color_iterator == checked_collors.end())
		{
			//Mark as checked.
			checked_collors.push_back(_building_area[i].GetColor());
		}
	}

	//If at least one building of each color was built, then a bonus of 3 needs to be added to the score.
	if (checked_collors.size() == 5)
	{
		score += 3;
	}

	//If this player was the first person to achieve 8 buildings, then a bonus of 4 needs to be added to the score.
	if (_first_to_eight_buildings)
	{
		score += 4;
	}
	//If this player has built 8 buildings, but was not the first to do so, then a bonus of 2 needs to be added to the score.
	else if (_building_area.size() >= 8)
	{
		score += 2;
	}

	return score;
}

const int Player::GetMoney() const
{
	return _money;
}

const std::vector<Building>& Player::LookAtBuildingsInHand() const
{
	return _available_buildings;
}

const std::vector<Building>& Player::LookAtConstructedBuildings() const
{
	return _building_area;
}

const bool Player::WasFirstToEightBuildings() const
{
	return _first_to_eight_buildings;
}

const bool Player::HasCharacter(const CharacterType character_type) const
{
	bool has_character = false;

	for (int i = 0; i < _characters.size(); i++)
	{
		//If has character.
		if (_characters[i].GetCharacterType() == character_type)
		{
			has_character = true;
		}
	}

	return has_character;
}

void Player::AddBuilding(const Building building)
{
	_available_buildings.push_back(building);
}

void Player::SwapBuildingCards(const std::vector<Building> new_buildings)
{
	_available_buildings = new_buildings;
}

void Player::AddCharacter(const Character character)
{
	_characters.push_back(character);
}

const bool Player::ConstructBuilding(const Building building)
{

	const auto building_iterator{ std::find(_available_buildings.begin(), _available_buildings.end(), building) };

	//If building not in hand, then the building cannot be constructed.
	if (building_iterator == _available_buildings.end())
	{
		return false;
	}
	else
	{
		//Add building to the building area.
		_building_area.push_back(building);

		//Remove building from hand.
		_available_buildings.erase(building_iterator);

		return true;
	}

}

void Player::DemolishBuilding(const unsigned short index)
{
	_building_area.erase(_building_area.begin() + index);
}

void Player::ResetCharacters()
{
	_characters.clear();
}

const bool Player::MutateMoney(const unsigned short money_balance)
{
	auto new_balance{ _money - money_balance };
	if (new_balance >= 0) {
		_money = new_balance;
		return true;
	}
	else {
		return false;
	}
}

void Player::EarnMoney(const unsigned short amount)
{
	_money += amount;
}

void Player::DeclareFirstToEight()
{
	_first_to_eight_buildings = true;
}
