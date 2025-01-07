#include <iostream>
#include "Debug/DebugMacros.h"
#include "Game.h"


int main()
{
	//Enable memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	DEBUG_LOG("SpriteBound started");

	Game game;
	game.Initialize();



	return 0;
}
