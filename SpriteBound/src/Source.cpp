#include <iostream>

#include "Debug/DebugMacros.h"
#include "Game.h"

int main()
{
	DEBUG_LOG("SpriteBound started");
	Game game;
	game.Initialize();
	return 0;
}
