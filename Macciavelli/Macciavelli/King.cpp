#include "King.h"

King::King(const std::shared_ptr<Player>& current_king) :
	_current_king {current_king}
{
}

void King::SetKing(const std::shared_ptr<Player>& king)
{
	_current_king = king;
}

const std::shared_ptr<Player>& King::GetKing() const
{
	return _current_king;
}
