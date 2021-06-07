#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "Game\Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	cGame::Get().Init();

	unsigned long luiLastTime = timeGetTime();

	while( !cGame::Get().HasFinished())
	{
		unsigned long luiActualTime = timeGetTime();
		float lfTimestep = ((float)(luiActualTime - luiLastTime) /1000.0f);
		luiLastTime = luiActualTime;

		cGame::Get().Update(lfTimestep);
		cGame::Get().Render();
	}

	cGame::Get().Deinit();
}