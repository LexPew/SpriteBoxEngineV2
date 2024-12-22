
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Tests/InputSystemTest.h"
#include "Tests/SmallDemoTest.h"
int main()
{
	//Enable memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Run the input system test
	SmallGameTest();
    return 0;
}
