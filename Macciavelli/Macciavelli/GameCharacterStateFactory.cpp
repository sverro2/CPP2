#include "GameCharacterStateFactory.h"
#include "GameCharacterMurdererState.h"
#include "GameCharacterThiefState.h"
#include "GameCharacterMagicianState.h"
#include "GameCharacterKingState.h"
#include "GameCharacterPriestState.h"
#include "GameCharacterMerchantState.h"
#include "GameCharacterArchitectState.h"
#include "GameCharacterCondottiereState.h"
#include "GameContext.h"

std::unique_ptr<GameState> GameCharacterStateFactory::GetCharacterState(CharacterType character_type, GameContext & context, IServer & server)
{
	std::unique_ptr<GameState> game_character_state;

	switch (character_type)
	{
	case MURDERER:
		game_character_state = std::make_unique<GameCharacterMurdererState>(context, server);
		break;
	case THIEF:
		game_character_state = std::make_unique<GameCharacterThiefState>(context, server);
		break;
	case MAGICIAN:
		game_character_state = std::make_unique<GameCharacterMagicianState>(context, server);
		break;
	case KING:
		game_character_state = std::make_unique<GameCharacterKingState>(context, server);
		break;
	case PRIEST:
		game_character_state = std::make_unique<GameCharacterPriestState>(context, server);
		break;
	case MERCHANT:
		game_character_state = std::make_unique<GameCharacterMerchantState>(context, server);
		break;
	case ARCHITECT:
		game_character_state = std::make_unique<GameCharacterArchitectState>(context, server);
		break;
	case CONDONTIERE:
		game_character_state = std::make_unique<GameCharacterCondottiereState>(context, server);
		break;
	default:
		break;
	}

	return game_character_state;
}
