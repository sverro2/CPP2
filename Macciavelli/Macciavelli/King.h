#pragma once
#include <memory>
#include "Player.h"

class King
{
public:
	King(const std::shared_ptr<Player>& current_king);

	//setter
	void SetKing(const std::shared_ptr<Player>& king);

	//getter
	const std::shared_ptr<Player>& GetKing() const;

private:
	std::shared_ptr<Player> _current_king;
};

