#pragma once
#include <memory>

class GameState;
class GameContext;
class IServer;
enum CharacterType;

class GameCharacterStateFactory
{
public:
	static std::unique_ptr<GameState> GetCharacterState(CharacterType character_type, GameContext& context, IServer& server);
};

